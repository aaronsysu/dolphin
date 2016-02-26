#pragma once
#include <vector>
#include <future>
#include <thread>
#include <queue>
#include <set>

namespace dolphin_base
{
	typedef std::function <void(void* param)> TaskHandlerFunc;
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
		//∑¢ÀÕ»ŒŒÒ
		void PostTask(TaskHandlerFunc func, void* param = nullptr);
		void PostDelayTask(__int64 delayTime, TaskHandlerFunc func, void* param = nullptr);

		void Start();
		void Stop();
	private:
		void RunTask();
		void RunDelayTask();

		std::queue<std::shared_ptr<TaskItem>> _pendingTasks;
		std::mutex _pendingTaskMutex;

		std::vector<std::pair<std::chrono::time_point<std::chrono::system_clock>, std::shared_ptr<TaskItem>>> _pendingTimeTasks;
		std::mutex _pendingTimeTaskMutex;

		std::vector<std::pair<unsigned int, std::shared_ptr<TaskItem>>> _pendingSocketTasks;
		std::mutex _pendingSocketTaskMutex;

		std::condition_variable _taskCv;
		std::vector<std::thread> _threads;

		bool exitFlag;
	};
}


