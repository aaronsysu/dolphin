#pragma once
#include <memory>
#include <map>
#include "MediaSession.h"
namespace dolphin_media
{
	typedef std::shared_ptr<MediaSession> MediaSessionPtr;
	class MediaMgr
	{
	public:
		MediaMgr();
		~MediaMgr();
		void CreateMediaSession(std::string param, std::string& sessionId);
		void DestroyMediaSession(const std::string& sessionId);
	protected:
		std::map<std::string, MediaSessionPtr> _mediaSessions;
	};
}
