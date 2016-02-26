#pragma once
#include <memory>
#include <map>
#include "Producer.h"
#include "Consumer.h"

namespace dolphin_media
{
	typedef std::shared_ptr<dolphin_base::Producer> ProducerPtr;
	typedef std::shared_ptr<dolphin_base::Consumer> ConsumerPtr;
	class MediaMgr
	{
	public:
		MediaMgr();
		~MediaMgr();
		static MediaMgr* Get(){
			static MediaMgr instance;
			return &instance;
		}
		void CreateMediaSession(std::string param, std::string& sessionId);
		void DestroyMediaSession(const std::string& sessionId);
	protected:
		std::map<std::string, ProducerPtr> _mediaSessions;
	};
}
