#pragma once
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>
namespace dolphin_common
{
	class ThreadPool
	{
	public:
		ThreadPool(int threadCount);
		~ThreadPool();
		void Start();
		void Stop();
	private:
		void _Run();
	private:
		bool _stop;
		int _threadCount;
		std::vector<std::thread> _threads;
		std::mutex _mtThread;
		std::condition_variable _cvWork;
	};
}