#include "stdafx.h"
#include "Thread.h"


namespace dolphin_common
{
	Thread::Thread()
	{
	}


	Thread::~Thread()
	{
	}

	void Thread::Start()
	{
		std::thread tmpWork([this](){
			Run();
		});
		_thrWork.swap(tmpWork);
	}

	void Thread::Stop()
	{
		_thrWork.join();
	}
}