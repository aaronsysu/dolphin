#pragma once
#include <thread>
namespace dolphin_common
{
	class Thread
	{
	public:
		Thread();
		~Thread();
		void Start();
		void Stop();
	protected:
		virtual void Run() = 0;
	private:
		std::thread _thrWork;
	};
}
