#include "stdafx.h"
#include "StreamServer.h"
#include <sstream>
#include "File.h"
#include "Path.h"

namespace dolphin_media
{
	StreamServer::StreamServer(std::string param)
		: dolphin_base::Consumer(param)
		, _playList(10, 4)
		, pCodec(NULL)
		, pEncoderCtx(NULL)
		, lastpts(0)
		, dst_context(nullptr)
		, _filecount(0)
		, firstTSCreated(false)
		, maxLastFiles(0)
	{
		if (maxLastFiles <= _playList.GetMaxItems())
			maxLastFiles = _playList.GetMaxItems() + 1;

		_workingDir = "";
	}


	StreamServer::~StreamServer()
	{
	}

	void StreamServer::Start()
	{
		av_register_all();

		CodecID AVCodecID = CODEC_ID_H264;

		// Find a suitable libavcodec encoder for H.264.
		pCodec = avcodec_find_encoder(AVCodecID);
		if (pCodec == NULL)
		{
			return;
		}

		dst_context = avformat_alloc_context();
		if (!dst_context)
		{
			return;
		}
		AVOutputFormat* format = av_guess_format(NULL, "test.mp4", NULL);
		if (!format)
		{
			avformat_free_context(dst_context);
			return;
		}
		format->video_codec = AVCodecID;
		dst_context->oformat = format;
		dst_context->packet_size = 0;
		dst_context->max_delay = 0;

		pst = avformat_new_stream(dst_context, NULL);
		if (!pst)
		{
			avformat_free_context(dst_context);
			return;
		}

		pEncoderCtx = pst->codec;
		if (dst_context->oformat->flags & AVFMT_GLOBALHEADER)
		{
			pEncoderCtx->flags |= CODEC_FLAG_GLOBAL_HEADER;
		}
		pEncoderCtx->codec_type = AVMEDIA_TYPE_VIDEO;
		pEncoderCtx->codec_id = AVCodecID;
		pEncoderCtx->bit_rate = 1 * 1000;
		pEncoderCtx->width = 720;
		pEncoderCtx->height = 480;
		//	pEncoderCtx->time_base = time_base;//(AVRational){1,ips};
		pEncoderCtx->time_base.num = 1;
		pEncoderCtx->time_base.den = 25;
		pEncoderCtx->gop_size = 100;
		pEncoderCtx->pix_fmt = PIX_FMT_YUV420P;//PIX_FMT_YUVJ420P
		if (AVCodecID == CODEC_ID_H264)
		{
			//pEncoder->keyint_min = gopsize;
			pEncoderCtx->bit_rate_tolerance = 0;
			//		pEncoderCtx->coder_type = FF_CODER_TYPE_VLC/*0*/;
			pEncoderCtx->coder_type = FF_CODER_TYPE_AC/*1*/;
			pEncoderCtx->max_b_frames = 2;
			pEncoderCtx->b_frame_strategy = 1;
			pEncoderCtx->qmin = 10;
			pEncoderCtx->qmax = 51;
			pEncoderCtx->rc_max_rate = 0;
			pEncoderCtx->rc_buffer_size = 0;
			pEncoderCtx->me_cmp = 1;
			pEncoderCtx->me_range = 16;
			pEncoderCtx->me_method = ME_ZERO;
			pEncoderCtx->me_subpel_quality = 5;
			pEncoderCtx->scenechange_threshold = 10000000;
			pEncoderCtx->flags |= CODEC_FLAG_LOOP_FILTER | CODEC_FLAG_LOW_DELAY;
			pEncoderCtx->i_quant_factor = (float)0.71;
			//		pEncoderCtx->weighted_p_pred = 0;
			//		pEncoderCtx->aq_mode = 0;
			//pEncoderCtx->thread_count = 1;

			/* This does not work
			int res = av_opt_set(pEncoderCtx->priv_data, "preset", "superfast", 0);
			if(res != 0)
			{
			LOG(error, "Error setting encoder private option [preset=superfast]");
			}
			//		av_opt_set(pEncoderCtx->priv_data, "tune", "zerolatency", 0);
			*/
		}

		dolphin_base::Consumer::Start();
	}

	void StreamServer::Stop()
	{
		dolphin_base::Consumer::Stop();
	}

	void StreamServer::ProcessFrame(dolphin_common::Frame::Ptr frame)
	{
		auto size = frame->GetFrameSize();
		auto buffer = frame->GetFrameBuf();
		
		if (size == 0)
		{
			return;
		}
		
		int AVres = 0;
		AVPacket pkt;
		av_init_packet(&pkt);

		if (frame->IsKeyFrame())
		{
			pkt.flags |= AV_PKT_FLAG_KEY;

			if (firstTSCreated)
			{
				AVres = av_write_trailer(dst_context);
				if (AVres != 0)
				{
				}
				AVres = avio_close(dst_context->pb);
				if (AVres != 0)
				{
				}

				WritePlaylist();
			}

			std::stringstream videofilename;
			videofilename << _workingDir << time(NULL) << ".ts";
			std::string video_file = videofilename.str();
			strncpy_s(dst_context->filename, video_file.c_str(), 1024);

			// Add new file to files lists.
			_playList.AppendItem(video_file);

			LastFiles.push_back(video_file);
			while (LastFiles.size() > maxLastFiles)
			{
				LastFiles.pop_front();
			}

			AVres = avio_open(&dst_context->pb, dst_context->filename, AVIO_FLAG_WRITE);
			if (AVres == 0)
			{
				AVres = avformat_write_header(dst_context, NULL);
				if (AVres != 0)
				{
					//LOG(error, Poco::format("Cannot write video file header [AVERROR: %d]", AVres));
				}
				firstTSCreated = true;
				_filecount++;
			}
			else
			{
				//LOG(error, Poco::format("Cannot open video file [AVERROR: %d]", AVres));
			}
		}
		
		if (_filecount > 0)
		{
			// Write video packet to file.
			pkt.stream_index = dst_context->streams[0]->index;
			pkt.data = (uint8_t*)buffer;
			pkt.size = size;
			lastpts += 1/*framediff*/ * 90;
			pkt.dts = lastpts;//AV_NOPTS_VALUE;
			pkt.pts = pkt.dts + 1;

			AVres = av_interleaved_write_frame(dst_context, &pkt);
			if (AVres != 0)
			{
			}
			av_free_packet(&pkt);
			//imgEncodedOk++;
			//imgcount++;
			return;
		}
	}

	void StreamServer::WritePlaylist()
	{
		if (!_playList.UpdateLivePlaylist(_workingDir + "video.m3u8"))
		{

		}

		// Delete oldest segment files.
		dolphin_common::File dir(_workingDir);
		std::vector<std::string> files;
		dir.GetFiles(files);
		for (auto it1 = files.begin(); it1 != files.end(); ++it1)
		{
			std::string& foundfile = *it1;
			bool to_remove = true;
			for (auto it2 = LastFiles.begin(); it2 != LastFiles.end(); ++it2)
			{
				if (it2->find(foundfile) != std::string::npos)
				{
					to_remove = false;
					break;
				}
			}
			if (to_remove && (foundfile.find(".ts") != std::string::npos || foundfile.find(".mp4") != std::string::npos))
			{
				std::string fileToRemove = foundfile;
				dolphin_common::File removeFile(fileToRemove);
				removeFile.Remove();
			}
		}
	}
}