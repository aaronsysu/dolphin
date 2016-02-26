#include "stdafx.h"
#include "Engine.h"

namespace dolphin_base
{
	Engine::Engine()
		: exitFlag(false){
	}


	Engine::~Engine(){

	}

	void Engine::PostTask(TaskHandlerFunc func, void* param){
		std::unique_lock<std::mutex> autolock(_pendingTaskMutex);
		TaskItem taskItem;
		taskItem.Attach(func, param);
		_pendingTasks.push(std::make_shared<TaskItem>(taskItem));

		_taskCv.notify_one();
	}

	void Engine::PostDelayTask(__int64 delayTime, TaskHandlerFunc func, void* param){
		typedef std::pair<std::chrono::time_point<std::chrono::system_clock>, std::shared_ptr<TaskItem>> taskItemType;
		std::unique_lock<std::mutex> autolock(_pendingTimeTaskMutex);

		auto nowTmpNow = std::chrono::system_clock::now();
		auto taskTime = nowTmpNow + std::chrono::milliseconds(delayTime);

		TaskItem taskItem;
		taskItem.Attach(func, param);
		_pendingTimeTasks.push_back(std::make_pair(taskTime, std::make_shared<TaskItem>(taskItem)));

		std::sort(std::begin(_pendingTimeTasks), std::end(_pendingTimeTasks), [](taskItemType& left, taskItemType& right)->bool{
			return left.first > right.first;
		});
	}

	void Engine::Start(){
		const int threadCount = 8;
		_threads.resize(threadCount + 1);

		//启动任务线程
		for (int i = 0; i < threadCount; i++){
			std::thread t(&Engine::RunTask, this);
			_threads[i].swap(t);
		}

		//启动定时器线程
		_threads[threadCount] = std::thread(&Engine::RunDelayTask, this);
	}

	void Engine::Stop(){
		exitFlag = true;
		_taskCv.notify_all();
		for (auto &it : _threads){
			it.join();
		}
		_threads.clear();
	}

	void Engine::RunTask(){
		std::queue<std::shared_ptr<TaskItem>> runningTasks;
		std::mutex handlingTask;

		std::shared_ptr<TaskItem> task = nullptr;

		while (true){
			std::unique_lock<std::mutex> autolock(handlingTask);
			_taskCv.wait(autolock);

			{
				std::unique_lock<std::mutex> autolock(_pendingTaskMutex);
				runningTasks.swap(_pendingTasks);
			}

			while (!runningTasks.empty()){
				auto task = runningTasks.front();
				task->RunTask();
				runningTasks.pop();
			}

			if (exitFlag){
				break;
			}
		}
	}

	void Engine::RunDelayTask(){
		typedef std::pair<std::chrono::time_point<std::chrono::system_clock>, std::shared_ptr<TaskItem>> timeTaskItemType;
		timeTaskItemType task;
		while (true){
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			{
				std::unique_lock<std::mutex> autolock(_pendingTimeTaskMutex);
				if (_pendingTimeTasks.empty()){
					continue;
				}
				task = _pendingTimeTasks.back();
			}
			auto nowTime = std::chrono::system_clock::now();
			if (task.first < nowTime){
				task.second->RunTask();

				std::unique_lock<std::mutex> autolock(_pendingTimeTaskMutex);
				_pendingTimeTasks.pop_back();
			}
			if (exitFlag){
				break;
			}
		}
	}
}