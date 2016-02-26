#include "stdafx.h"
#include "HttpServer.h"
#include <stdlib.h>
#include <stdio.h>
#include "Utility.h"
#include "libevent_struct.h"

HttpServer::HttpServer()
{
}


HttpServer::~HttpServer()
{
	_httpWorker.join();
}

void HttpServer::GenericHandler(struct evhttp_request *req, void *arg)
{
	HttpServer* httpServer = (HttpServer*)arg;
	if (nullptr != httpServer)
	{
		httpServer->HandleRequest(req);
	}
}

void HttpServer::HandleRequest(struct evhttp_request *req)
{
	const evhttp_uri* uri = evhttp_request_get_evhttp_uri(req);
	const char* path = evhttp_uri_get_path(uri);

	if (path == nullptr || strlen(path) == 0)
	{
		evhttp_send_error(req, HTTP_NOTFOUND, "Not Found");
		return;
	}

	std::string method = "unknown";
	switch (req->type)
	{
	case EVHTTP_REQ_GET:
		method = "get";
		break;
	case EVHTTP_REQ_POST:
		method = "post";
		break;
	case EVHTTP_REQ_PUT:
		method = "put";
		break;
	case EVHTTP_REQ_DELETE:
		method = "delete";
		break;
	default:
		break;
	}

	auto requestProc = GetRequestProc(path, method);
	if (requestProc == nullptr)
	{
		evhttp_send_error(req, HTTP_NOTFOUND, "Not Found");
		return;
	}

	std::map<std::string, std::string> params;
	GetRequestParams(req, params);

	requestProc(params, [req](int type, std::string msg)->void{
		if (type == HTTP_OK)
		{
			struct evbuffer *body = nullptr;
			if (!msg.empty())
			{
				body = evbuffer_new();
				evbuffer_add_printf(body, "%s", msg.c_str());
			}

			evhttp_send_reply(req, HTTP_OK, "OK", body);

			if (body != nullptr)
			{
				evbuffer_free(body);
			}
		}
		else
		{
			evhttp_send_error(req, type, nullptr);
		}
	});
}

void HttpServer::GetRequestParams(struct evhttp_request *req, std::map<std::string, std::string> &params)
{
	evkeyvalq headers;
	const char* tmpUri = evhttp_request_get_uri(req);
	evhttp_parse_query(tmpUri, &headers);

	auto nextParam = headers.tqh_first;
	while (nextParam != nullptr)
	{
		if (nextParam->key != nullptr && nextParam->value != nullptr)
		{
			params[nextParam->key] = nextParam->value;
		}
		nextParam = nextParam->next.tqe_next;
	}
}

const std::function<void(std::map<std::string, std::string>, std::function<void(int, std::string)>)> HttpServer::GetRequestProc(const std::string uri, const std::string method)
{
	std::string tmp = uri + ":" + method;
	auto it = _uriMap.find(tmp);

	if (it != _uriMap.end())
	{
		return it->second;
	}
	else
	{
		if (uri.size() == 0)
		{
			return nullptr;
		}
		if (uri[uri.size() - 1] == '/')
		{
			return GetRequestProc(uri.substr(0, uri.size() - 1), method);
		}
		else if (uri[uri.size() - 1] != '*')
		{
			std::string::size_type pos = uri.find("/", 1);
			if (pos >= 1)
			{
				std::string newUri = uri.substr(0, pos) + '*';
				return GetRequestProc(newUri, method);
			}
		}
	}

	return nullptr;
}

//param: httpPort=80;httpAddress=127.0.0.1;
void HttpServer::Start(std::string param, std::function<void()> onSuccess, std::function<void()> onError)
{
	std::thread tmpThreadWork([param, this](){
		short httpPort = 80;
		std::string httpAddress = "127.0.0.1";
		if (!param.empty())
		{
			dolphin_utility::Utility::GetParam(param, "httpAddress", httpAddress);
			dolphin_utility::Utility::GetParam(param, "httpPort", httpPort);
		}
		_evBase = event_base_new();

		_httpServer = evhttp_new(_evBase);
		if (nullptr == _httpServer)
		{
			return;
		}

		int ret = evhttp_bind_socket(_httpServer, httpAddress.c_str(), httpPort);
		if (ret != 0)
		{
			return;
		}

		evhttp_set_gencb(_httpServer, GenericHandler, this);
		event_base_dispatch(_evBase);
	});
	_httpWorker.swap(tmpThreadWork);
}

void HttpServer::Stop()
{
	int iError = 0;
	iError = event_base_loopbreak(_evBase);
	if (iError != 0)
	{
		//LOG
	}
	event_base_free(_evBase);
	evhttp_free(_httpServer);
	_httpWorker.join();
}

void HttpServer::RegisterUri(const std::string method, const std::string uri, std::function<void(std::map<std::string, std::string>, std::function<void(int, std::string)>)> onHandleHttpRequest)
{
	std::string tmp = uri + ":" + method;
	if (_uriMap.find(tmp) != _uriMap.end())
	{
		return;
	}
	_uriMap[tmp] = onHandleHttpRequest;
}