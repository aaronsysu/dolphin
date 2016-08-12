#pragma once
#include <memory>
#include <thread>
#include "Consumer.h"
#include "InternalDefines.h"
#include "../../common/thread/MessageQueue.h"

extern "C"{
#include "../../thirdparty/ffmpeg/include/libavcodec/avcodec.h"
#include "../../thirdparty/ffmpeg/include/libavutil/avutil.h"
#include "../../thirdparty/ffmpeg/include/libavformat/avformat.h"
}

class MediaDecoder
	: public Consumer<MediaSample::Ptr>
	, public Producer<MediaSample::Ptr>
{
public:
	MediaDecoder();
	~MediaDecoder();
	void Start();
	void Stop();
	unsigned Width();
	unsigned Height();
private:
	virtual void Push(MediaSample::Ptr &buffer) override;
	void Decode(MediaSample::Ptr buffer);
	void Run();
private:
	bool m_bShutdown;
	std::thread m_worker;
	COMMON::THREAD::MessageQueue<MediaSample::Ptr> m_bufferQueue;

	AVCodecContext* m_codecContext{};
	AVFrame* m_avFrame;
};

