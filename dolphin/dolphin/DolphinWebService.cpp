#include "stdafx.h"
#include "DolphinWebService.h"
#include "MediaMgr.h"
#include "cJSON.h"

namespace dolphin_web
{
	DolphinWebService::DolphinWebService()
	{
	}


	DolphinWebService::~DolphinWebService()
	{
	}

	void DolphinWebService::Start()
	{
		_httpServer.RegisterUri("get", "/thumb*", [this](ParamsMap params, ResponseFunc onResponse)->void{
			OnHandleGetThumbnail(params, onResponse);
		});
		_httpServer.RegisterUri("get", "/source*", [this](ParamsMap params, ResponseFunc onResponse)->void{
			OnHandleSources(params, onResponse);
		});
		_httpServer.RegisterUri("post", "/stream/create", [this](ParamsMap params, ResponseFunc onResponse)->void{
			OnHandleStreamCreate(params, onResponse);
		});
		_httpServer.RegisterUri("post", "/stream/destroy", [this](ParamsMap params, ResponseFunc onResponse)->void{
			OnHandleStreamDestory(params, onResponse);
		});
		_httpServer.RegisterUri("get", "/stream", [this](ParamsMap params, ResponseFunc onResponse)->void{
			OnHandleStreamDestory(params, onResponse);
		});
		_httpServer.Start("httpPort=8888;httpAddress=10.82.13.95");
	}

	void DolphinWebService::Stop()
	{
		_httpServer.Stop();
	}

	void DolphinWebService::OnHandleError(std::string param)
	{

	}

	void DolphinWebService::OnHandleStreamCreate(ParamsMap params, ResponseFunc onResponse)
	{
		std::string sessionId;
		dolphin_media::MediaMgr::Get()->CreateMediaSession("", sessionId);

		if (onResponse != nullptr)
		{
			cJSON * responseString = cJSON_CreateObject();
			cJSON_AddItemToObject(responseString, "sid", cJSON_CreateString(sessionId.c_str()));
			std::string responseParam = cJSON_PrintUnformatted(responseString);
			cJSON_Delete(responseString);

			onResponse(200, responseParam);
		}
	}

	void DolphinWebService::OnHandleStreamDestory(ParamsMap param, ResponseFunc onResponse)
	{
		std::string sessionId;
		sessionId = param["sid"];
		dolphin_media::MediaMgr::Get()->DestroyMediaSession(sessionId);

		if (onResponse != nullptr)
		{
			onResponse(200, "");
		}

	}

	void DolphinWebService::OnHandleSources(ParamsMap param, ResponseFunc onResponse)
	{
		if (onResponse != nullptr)
		{
			cJSON * responseString = cJSON_CreateObject();
			std::string responseParam = cJSON_PrintUnformatted(responseString);
			cJSON_Delete(responseString);

			onResponse(200, responseParam);
		}
	}

	void DolphinWebService::OnHandleGetThumbnail(ParamsMap param, ResponseFunc onResponse)
	{
		if (onResponse != nullptr)
		{
			onResponse(200, "");
		}
	}
}