#pragma once
#include <vector>
#include <future>
#include <thread>
#include <queue>
#include <set>
#include "Producer.h"
#include "Consumer.h"

#ifdef WIN32
#include <WinSock2.h>
#include <windows.h>
#endif

namespace dolphin_base
{
	typedef std::function <bool(void* param)> TaskHandlerFunc;
	class TaskItem
	{
	public:
		TaskItem(){
			_taskId = "";//Generate uuid
		}
		void Attach(TaskHandlerFunc fn, void* p = nullptr){
			_func = fn;
			_param = p;
		}
		void RunTask(){
			if (_func == nullptr){
				return;
			}
			_func(_param);
		}
	protected:
		TaskHandlerFunc _func;
		void* _param;
		std::string _taskId;
	};
	class Engine
	{
	public:
		Engine();
		~Engine();
		static Engine* Get(){
			static Engine engine;
			return &engine;
		}
		//Task
		void PostTask(TaskHandlerFunc func);
		void PostDelayTask(TaskHandlerFunc func, __int64 delayTime);

		void Start();
		void Stop();
	private:
		void RunTask();
		void RunDelayTask();

		std::queue<std::shared_ptr<TaskItem>> _pendingTasks;
		std::mutex _pendingTaskMutex;

		std::vector<std::pair<time_t, std::shared_ptr<TaskItem>>> _pendingTimeTasks;
		std::mutex _pendingTimeTaskMutex;

		std::vector<std::pair<unsigned int, std::shared_ptr<TaskItem>>> _pendingSocketTasks;
		std::mutex _pendingSocketTaskMutex;

		std::condition_variable _taskCv;
		std::vector<std::thread> _threads;

		bool exitFlag;
	};
}


