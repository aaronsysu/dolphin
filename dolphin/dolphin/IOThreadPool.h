#pragma once
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
namespace dolphin_common
{
#ifdef WIN32
	typedef HANDLE DLPN_HANDLE;
#endif

#define IOTHREADPOOL_STOP (-1)
#define IOTHREADPOOL_EVENT (-2)

#define IOBUFFER_LEN 8192
	class IONotificationObj;
	struct IOCONTEXT
	{
		DLPN_HANDLE			_handle;
		int					_opType;
		WSABUF				_wsaBuf;
		OVERLAPPED			_overlapped;
		IONotificationObj*	_obj;
		void ResetBuffer()
		{
			_wsaBuf.len = IOBUFFER_LEN;
			memset(_wsaBuf.buf, 0, IOBUFFER_LEN);
			memset(&_overlapped, 0, sizeof(OVERLAPPED));
		}
		IOCONTEXT()
		{
			_handle = INVALID_HANDLE_VALUE;
			_opType = 0;
			_wsaBuf.buf = new char[IOBUFFER_LEN];
			_wsaBuf.len = IOBUFFER_LEN;
			_obj = nullptr;
			memset(_wsaBuf.buf, 0, IOBUFFER_LEN);
			memset(&_overlapped, 0, sizeof(OVERLAPPED));
		}
		~IOCONTEXT()
		{
			delete[] _wsaBuf.buf;
		}
	};

	class IONotificationObj
	{
		friend class IOThreadPool;
	protected:
		IOCONTEXT* GetNewIOContext()
		{
			IOCONTEXT* newIOContext = new IOCONTEXT;
			newIOContext->_obj = this;
			return newIOContext;
		}
	protected:
		virtual void OnConnect() = 0;
		virtual void OnDisconnect() = 0;
		virtual void OnNotify(IOCONTEXT* context) = 0;
	};

	class IOThreadPool
	{
	public:
		IOThreadPool(int threadCount);
		~IOThreadPool();
		static IOThreadPool* Get(){
			static IOThreadPool instance(8);
			return &instance;
		}
		void Start();
		void Stop();
		void Notify(IOCONTEXT* obj);
		//关联完成端口
		void AssociatePort(IOCONTEXT* obj);
	protected:
		void Run();
	protected:
		int _threadCount;
		std::vector<std::thread> _threads;
		DLPN_HANDLE _iocpHandle;
	};

}