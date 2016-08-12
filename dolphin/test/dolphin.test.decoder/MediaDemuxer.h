#pragma once
#include "Consumer.h"
#include "InternalDefines.h"
#include <thread>

extern "C"{
#include "../../thirdparty/ffmpeg/include/libavformat/avformat.h"
}

class MediaDemuxer 
	: public Producer<MediaSample::Ptr>
{
public:
	MediaDemuxer();
	~MediaDemuxer();
	void Start();
	void Stop();
private:
	void Run();
private:
	bool m_bShutdown;
	std::thread m_worker;
	std::string m_fileName;
	AVFormatContext* m_avFormatContext;
};

