#include "stdafx.h"
#include "IOThreadPool.h"


namespace dolphin_common
{
	IOThreadPool::IOThreadPool(int threadCount)
		: _threadCount(threadCount)
		, _iocpHandle(INVALID_HANDLE_VALUE)
	{
		_threads.resize(_threadCount);
	}


	IOThreadPool::~IOThreadPool()
	{
	}

	void IOThreadPool::Start()
	{
		if (_iocpHandle == INVALID_HANDLE_VALUE)
		{
			_iocpHandle = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, (DWORD)_threadCount);
		}
		for (int i = 0; i < _threadCount; i++)
		{
			_threads[i].swap(std::thread([=]{
				Run();
			}));
		}
	}

	void IOThreadPool::Stop()
	{
		for (int i = 0; i < _threadCount; i++)
		{
			::PostQueuedCompletionStatus(_iocpHandle, IOTHREADPOOL_STOP, 0, 0);
		}
		for (int i = 0; i < _threadCount; i++)
		{
			_threads[i].join();
		}
		::CloseHandle(_iocpHandle);
		_iocpHandle = INVALID_HANDLE_VALUE;
	}

	void IOThreadPool::AssociatePort(IOCONTEXT* obj)
	{
		HANDLE h = ::CreateIoCompletionPort(obj->_handle, _iocpHandle, (ULONG_PTR)obj, _threadCount);
		if (h == INVALID_HANDLE_VALUE)
		{
			//LOG ATTACH FAILED
			return;
		}
	}

	void IOThreadPool::Run()
	{
		DWORD numberOfBytesTransferred = 0;
		HANDLE hIOFd = NULL;
		ULONG_PTR key = 0;
		LPOVERLAPPED ovl = NULL;
		BOOL bRet = FALSE;
		DWORD dwError = 0;
		typedef enum
		{
			iocp_quit,
			iocp_event
		}iocp_flag;
		iocp_flag flag = iocp_event;

		while (flag != iocp_quit)
		{
			bRet = GetQueuedCompletionStatus(
				_iocpHandle, 
				&numberOfBytesTransferred, 
				&key,
				&ovl,
				INFINITE);
			if (!bRet)
			{
				dwError = GetLastError();
				flag = iocp_quit;
				continue;
			}
			else
			{
				IOCONTEXT* pIOObj = reinterpret_cast<IOCONTEXT*>(key);
				if (0 == numberOfBytesTransferred)
				{
					//客户端断开连接
					if (pIOObj)
					{
						pIOObj->_obj->OnNotify(pIOObj);
						delete pIOObj;
					}
					continue;
				}
				else if (IOTHREADPOOL_STOP == pIOObj->_opType)
				{
					flag = iocp_quit;
					continue;
				}

				if (pIOObj)
				{
					pIOObj->_obj->OnNotify(pIOObj);
					delete pIOObj;
				}
			}
		}
	}

	void IOThreadPool::Notify(IOCONTEXT* obj)
	{
		::PostQueuedCompletionStatus(_iocpHandle, IOTHREADPOOL_EVENT, (ULONG_PTR)obj, nullptr);
	}

}