#pragma once
#include "InternalDefines.h"
#include <memory>
class MediaDisplay;
class MediaDecoder;
class MediaReciever;
class MediaDemuxer;
class MediaManager
{
public:
	MediaManager();
	~MediaManager();
	static void Init();
	static void UnInit();
	static MediaManager* Get();
	void Start();
	void Stop();
	void Run();
private:
	static MediaManager* m_instance;
	std::shared_ptr<MediaDecoder> m_mediaDecoder;
	std::shared_ptr<MediaReciever> m_mediaReciever;
	std::shared_ptr<MediaDisplay> m_mediaDisplay;
	std::shared_ptr<MediaDemuxer> m_mediaDemuxer;
};

