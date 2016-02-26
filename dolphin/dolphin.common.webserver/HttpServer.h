#pragma once
#include <functional>
#include <thread>
#include <map>
#include <event2/event.h>
#include <event2/buffer.h>
#include <event2/http.h>

class HttpServer
{
public:
	HttpServer();
	~HttpServer();
	static HttpServer* Get(){
		static HttpServer instance;
		return &instance;
	}
	void Start(std::string param, std::function<void()> onSuccess = nullptr,
		std::function<void()> onError = nullptr);
	void Stop();
	void RegisterUri(const std::string method, const std::string uri, std::function<void(std::map<std::string, std::string>, std::function<void(int, std::string)>)> onHandleHttpRequest = nullptr);
private:
	static void GenericHandler(struct evhttp_request *req, void *arg);
	void HandleRequest(struct evhttp_request *req);
	void GetRequestParams(struct evhttp_request *req, std::map<std::string, std::string> &params);
	const std::function<void(std::map<std::string, std::string>, std::function<void(int, std::string)>)> GetRequestProc(const std::string uri, const std::string method);
private:
	std::map<std::string, std::function<void(std::map<std::string, std::string>, std::function<void(int, std::string)>)>> _uriMap;

	std::thread _httpWorker;

	event_base* _evBase;
	evhttp* _httpServer;
};

