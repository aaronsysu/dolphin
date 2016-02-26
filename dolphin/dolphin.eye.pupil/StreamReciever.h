#pragma once
#include "Thread.h"
namespace dolphin_stream
{
	class StreamReciever
		: public dolphin_common::Thread
	{
	public:
		StreamReciever();
		~StreamReciever();
		void Start();
		void Stop();
	private:
		void Run();
		unsigned char*	_streamBuffer;
		unsigned int	_streamBufferSize;
	};
}
