#include "stdafx.h"
#include "MediaDecoder.h"

extern "C"{
#pragma comment(lib, "../../thirdParty/ffmpeg/lib/avformat.lib")
#pragma comment(lib, "../../thirdParty/ffmpeg/lib/avcodec.lib")
#pragma comment(lib, "../../thirdParty/ffmpeg/lib/swscale.lib")
#pragma comment(lib, "../../thirdParty/ffmpeg/lib/avutil.lib")
}

MediaDecoder::MediaDecoder()
	: m_avFrame(nullptr)
	, m_bShutdown(false)
{
}


MediaDecoder::~MediaDecoder()
{
}

void MediaDecoder::Start()
{
	av_register_all();

	m_worker.swap(std::thread(std::bind(&MediaDecoder::Run, this)));
}

void MediaDecoder::Stop()
{
	m_bShutdown = true;
	m_worker.join();

	avcodec_close(m_codecContext);
}

void MediaDecoder::Run()
{
	MediaSample::Ptr buffer = nullptr;
	if (nullptr == m_codecContext)
	{
		m_codecContext = avcodec_alloc_context();

		AVCodec* codec = avcodec_find_decoder(CODEC_ID_H264);
		if (codec && avcodec_open(m_codecContext, codec) >= 0)
		{
			m_avFrame = avcodec_alloc_frame();
		}
		else if (m_codecContext)
		{
			av_free(m_codecContext);
		}
	}

	while (!m_bShutdown)
	{
		m_bufferQueue.Wait_and_pop(buffer);

		Decode(buffer);
	}
}

void MediaDecoder::Decode(MediaSample::Ptr buffer)
{
	if (nullptr == m_codecContext)
		return;

	AVPacket avPacket;
	av_init_packet(&avPacket);
	avPacket.data = buffer->buffer;
	avPacket.size = buffer->bufferSize;

	int picPtr = 0;

	int decodedSize = avcodec_decode_video2(m_codecContext, m_avFrame, &picPtr, &avPacket);
	if (picPtr)
	{
		MediaSample::Ptr newBuffer = std::make_shared<MediaSample>();
		newBuffer->planes[0] = m_avFrame->data[0];
		newBuffer->planes[1] = m_avFrame->data[1];
		newBuffer->planes[2] = m_avFrame->data[2];
		newBuffer->pitches[0] = static_cast<size_t>(m_avFrame->linesize[0]);
		newBuffer->pitches[1] = static_cast<size_t>(m_avFrame->linesize[1]);
		newBuffer->pitches[2] = static_cast<size_t>(m_avFrame->linesize[2]);

		PushToConsumer(newBuffer);
	}
}

void MediaDecoder::Push(MediaSample::Ptr &buffer)
{
	m_bufferQueue.Push_and_notify(buffer);
}

unsigned MediaDecoder::Width()
{
	return nullptr == m_codecContext? 0 : m_codecContext->width;
}

unsigned MediaDecoder::Height()
{
	return nullptr == m_codecContext ? 0 : m_codecContext->height;
}
