#include "stdafx.h"
#include "MediaMgr.h"

namespace dolphin_media
{
	MediaMgr::MediaMgr()
	{
	}

	MediaMgr::~MediaMgr()
	{
	}

	void MediaMgr::CreateMediaSession(std::string param, std::string& sessionId)
	{
		MediaSessionPtr session = std::make_shared<MediaSession>(param);
		_mediaSessions[sessionId] = session;
	}

	void MediaMgr::DestroyMediaSession(const std::string& sessionId)
	{

	}
}
