#include "stdafx.h"
#include "MediaMgr.h"
#include "StreamProcducer.h"
#include "HttpLiveStreamServer.h"
#include "RecordConsumer.h"
#include "UUID.h"

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
		//Parse param
		std::string tag = "RTSP";
		ProducerPtr producer = std::make_shared<StreamProcducer>(tag);
		ConsumerPtr consumer = std::make_shared<HttpLiveStreamServer>("");
		ConsumerPtr recConsumer = std::make_shared<dolphin_storage::RecordConsumer>("");
		
		producer->AttachConsumer(consumer);
		producer->AttachConsumer(recConsumer);
		consumer->Start();
		recConsumer->Start();
		producer->Start();

		//generate uuid
		dolphin_common::UUIDGen gen;
		sessionId = gen.GetNewUuid();

		_mediaSessions[sessionId] = producer;
	}

	void MediaMgr::DestroyMediaSession(const std::string& sessionId)
	{
		auto it = _mediaSessions.find(sessionId);
		if (it == _mediaSessions.end())
		{
			return;
		}
		ProducerPtr session = it->second;
		session->Stop();

		_mediaSessions.erase(it);
	}
}
