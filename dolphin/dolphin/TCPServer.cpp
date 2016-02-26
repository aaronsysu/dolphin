#include "stdafx.h"
#include "TCPServer.h"

namespace dolphin_common
{
#define MAX_POST_ACCEPT 10

	TCPServer::TCPServer()
	{
		_acceptEx = nullptr;
		_getAcceptExSockAddrs = nullptr;
		_socket = INVALID_SOCKET;
	}


	TCPServer::~TCPServer()
	{
	}

	void TCPServer::Start(const std::string& addr, unsigned short port)
	{
		GUID GuidAcceptEx = WSAID_ACCEPTEX;
		GUID GuidGetAcceptExSockAddrs = WSAID_GETACCEPTEXSOCKADDRS;

		_socket = ::WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);

		if (INVALID_SOCKET == _socket)
		{
			//LOG FAILED
			return;
		}

		IOCONTEXT* pNewContext = GetNewIOContext();
		pNewContext->_handle = (HANDLE)_socket;
		pNewContext->_opType = 2556;
		IOThreadPool::Get()->AssociatePort(pNewContext);

		BOOL lVal = 1;
		::setsockopt(_socket, SOL_SOCKET, SO_KEEPALIVE, (char*)&lVal, sizeof(BOOL));
		SOCKADDR_IN saLocal;
		memset(&saLocal, 0, sizeof(SOCKADDR_IN));
		saLocal.sin_family = AF_INET;
		saLocal.sin_addr.s_addr = INADDR_ANY;//inet_addr(addr.c_str());
		saLocal.sin_port = htons(port);

		int iRet = 0;
		iRet = ::bind(_socket, (const sockaddr*)&saLocal, sizeof(SOCKADDR_IN));
		if (iRet != 0)
		{
			::closesocket(_socket);
			_socket = INVALID_SOCKET;
			return;
		}
		
		if (SOCKET_ERROR == ::listen(_socket, 5))
		{
			//LOG FAILED
			::closesocket(_socket);
			return;
		}

		DWORD dwBytes = 0;
		if (SOCKET_ERROR == WSAIoctl(
			_socket,
			SIO_GET_EXTENSION_FUNCTION_POINTER,
			&GuidAcceptEx,
			sizeof(GuidAcceptEx),
			&_acceptEx,
			sizeof(_acceptEx),
			&dwBytes,
			NULL,
			NULL))
		{
			::closesocket(_socket);
			return;
		}
		if (SOCKET_ERROR == WSAIoctl(
			_socket,
			SIO_GET_EXTENSION_FUNCTION_POINTER,
			&GuidGetAcceptExSockAddrs,
			sizeof(GuidGetAcceptExSockAddrs),
			&_getAcceptExSockAddrs,
			sizeof(_getAcceptExSockAddrs),
			&dwBytes,
			NULL,
			NULL))
		{
			::closesocket(_socket);
			return;
		}

		if (false == PostAccept())
		{
			return;
		}
	}

	void TCPServer::Stop()
	{
		if (_socket != INVALID_SOCKET)
		{
			closesocket(_socket);
			_socket = INVALID_SOCKET;
		}
	}

	void TCPServer::OnNotify(IOCONTEXT* context)
	{

	}

	void TCPServer::OnConnect()
	{

	}

	void TCPServer::OnDisconnect()
	{

	}

	bool TCPServer::PostAccept()
	{
		DWORD dwBytes = 0;
		IOCONTEXT* context = GetNewIOContext();
		context->_opType = 1001;

		// 为以后新连入的客户端先准备好Socket( 这个是与传统accept最大的区别 ) 
		context->_handle = (HANDLE)WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
		if (INVALID_SOCKET == (SOCKET)context->_handle)
		{
			return false;
		}

		// 投递AcceptEx
		if (FALSE == _acceptEx(_socket, 
			(SOCKET)context->_handle, 
			context->_wsaBuf.buf, 
			context->_wsaBuf.len - ((sizeof(SOCKADDR_IN) + 16) * 2),
			sizeof(SOCKADDR_IN) + 16, 
			sizeof(SOCKADDR_IN) + 16, 
			&dwBytes, 
			&context->_overlapped))
		{
			if (WSA_IO_PENDING != WSAGetLastError())
			{
				return false;
			}
		}

		return true;

	}
}