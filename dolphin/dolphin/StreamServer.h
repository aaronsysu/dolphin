#pragma once
#include "Consumer.h"
#include "Playlist.h"
namespace dolphin_media
{
	class StreamServer :
		public dolphin_base::Consumer
	{
	public:
		StreamServer(std::string param);
		~StreamServer();
		virtual void Start();
		virtual void Stop();
		virtual void ProcessFrame(dolphin_common::Frame::Ptr frame);
	private:
		void WritePlaylist();
	private:
		AVCodec         *pCodec;
		AVCodecContext  *pEncoderCtx;
		AVFormatContext	*dst_context;
		AVStream 		*pst;

		int lastpts;

		Playlist _playList;
		unsigned long int _filecount;
		unsigned int maxLastFiles;
		std::string _workingDir;
		std::list<std::string> LastFiles;
		bool firstTSCreated;
	};
}
