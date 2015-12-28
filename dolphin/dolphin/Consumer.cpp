#include "stdafx.h"
#include "Consumer.h"

namespace dolphin_base
{
	Consumer::Consumer(){
	}


	Consumer::~Consumer(){
	}

	void Consumer::PushFrame(dolphin_common::Frame::Ptr frame)
	{
		dolphin_common::QueueElementPtr elem = dolphin_common::QueueElement::CreateNewElem();
		elem->SetObj(frame.get());
		_blockingQueue.EnQueue(elem);
	}

	dolphin_common::Frame::Ptr Consumer::PopFrame(){
		dolphin_common::QueueElementPtr elem = _blockingQueue.DeQueueBlocking(10);
		if (elem == nullptr){
			return nullptr;
		}
		dolphin_common::Frame::Ptr frame = std::make_shared<dolphin_common::Frame>();
		frame.reset(reinterpret_cast<dolphin_common::Frame*>(elem->GetObj()));

		return frame;
	}

	void Consumer::RunCircle(){
		dolphin_common::Frame::Ptr frame = PopFrame();
		if (frame == nullptr){
			return;
		}
		ProcFrame(frame);
	}
}