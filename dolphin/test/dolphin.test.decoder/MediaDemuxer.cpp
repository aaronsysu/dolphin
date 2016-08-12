#include "stdafx.h"
#include "MediaDemuxer.h"

MediaDemuxer::MediaDemuxer()
	: m_avFormatContext(nullptr)
	, m_bShutdown(false)
{
	m_fileName = "./test.avi";
#ifdef WIN32
	DWORD dwExePathName = MAX_PATH * 2;
	char szExePathName[MAX_PATH * 2];

	::GetModuleFileNameA(NULL, szExePathName, dwExePathName);

	std::string strAppDir = szExePathName;
	strAppDir.erase(strAppDir.rfind('\\'));
	m_fileName = strAppDir + "\\test.avi";
#else
	m_fileName = "test.avi";
#endif
	av_register_all();
}


MediaDemuxer::~MediaDemuxer()
{
}

void MediaDemuxer::Start()
{
	int err = 0;
	err = avformat_open_input(&m_avFormatContext, m_fileName.c_str(), nullptr, nullptr);
	avformat_find_stream_info(m_avFormatContext, nullptr);
	av_find_best_stream(m_avFormatContext, AVMEDIA_TYPE_VIDEO, -1, -1, nullptr, 0);

	m_worker.swap(std::thread(std::bind(&MediaDemuxer::Run, this)));
}

void MediaDemuxer::Stop()
{
	m_bShutdown = true;
	m_worker.join();
	avformat_close_input(&m_avFormatContext);
}

void MediaDemuxer::Run()
{
	while (!m_bShutdown)
	{
		if (m_avFormatContext == nullptr)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			continue;
		}
		AVPacket avPacket;
		av_read_frame(m_avFormatContext, &avPacket);

		if (avPacket.size == 0)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			continue;
		}

		auto newBuffer = std::make_shared<MediaSample>();
		unsigned char* buffer = new unsigned char[avPacket.size];
		memcpy(buffer, avPacket.data, avPacket.size);

		newBuffer->buffer = buffer;
		newBuffer->bufferSize = avPacket.size;
		PushToConsumer(newBuffer);
	}
}