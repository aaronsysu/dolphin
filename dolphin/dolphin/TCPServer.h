#pragma once
#include "IOThreadPool.h"
#ifdef WIN32
#include <MSWSock.h>
#endif

namespace dolphin_common
{
	class TCPServer :
		public IONotificationObj
	{
	public:
		TCPServer();
		~TCPServer();
		void Start(const std::string& addr, unsigned short port);
		void Stop();
		void OnNotify(IOCONTEXT* context);
		void OnConnect();
		void OnDisconnect();
	private:
		bool PostAccept();
	private:
		SOCKET _socket;
#ifdef WIN32
		LPFN_ACCEPTEX                _acceptEx;
		LPFN_GETACCEPTEXSOCKADDRS    _getAcceptExSockAddrs;
#endif
	};

}