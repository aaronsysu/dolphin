#include "stdafx.h"
#include "ThreadPool.h"


namespace dolphin_common
{
	ThreadPool::ThreadPool(int threadCount)
		: _threadCount(threadCount)
		, _stop(false)
	{
		_threads.resize(_threadCount);
	}

	ThreadPool::~ThreadPool()
	{
	}

	void ThreadPool::Start()
	{
		for (int i = 0; i < _threadCount; i++)
		{
			_threads[i].swap(std::thread([=]{
				_Run();
			}));
		}
	}

	void ThreadPool::Stop()
	{
		_stop = true;
	}

	void ThreadPool::_Run()
	{
		while (!_stop)
		{
			std::unique_lock<std::mutex> autolock(_mtThread);
			_cvWork.wait_for(autolock, std::chrono::microseconds(10));
		}
	}
}