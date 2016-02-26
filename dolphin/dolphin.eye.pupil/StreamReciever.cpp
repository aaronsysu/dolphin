#include "stdafx.h"
#include "StreamReciever.h"


namespace dolphin_stream
{
	StreamReciever::StreamReciever()
	{
	}


	StreamReciever::~StreamReciever()
	{
	}

	void StreamReciever::Start()
	{
		dolphin_common::Thread::Start();
	}

	void StreamReciever::Stop()
	{
		dolphin_common::Thread::Stop();
	}

	void StreamReciever::Run()
	{

	}

}