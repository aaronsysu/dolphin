#pragma once
#include "../dolphin.common.webserver/HttpServer.h"
namespace dolphin_web
{
	typedef std::map<std::string, std::string> ParamsMap;
	typedef std::function<void(int, std::string)> ResponseFunc;
	class DolphinWebService
	{
	public:
		DolphinWebService();
		~DolphinWebService();
		void Start();
		void Stop();
	private:
		void OnHandleError(std::string param);
		void OnHandleStreamCreate(ParamsMap param, ResponseFunc onResponse);
		void OnHandleStreamDestory(ParamsMap param, ResponseFunc onResponse);
		void OnHandleSources(ParamsMap param, ResponseFunc onResponse);
		void OnHandleGetThumbnail(ParamsMap param, ResponseFunc onResponse);
	private:
		HttpServer _httpServer;
	};
}