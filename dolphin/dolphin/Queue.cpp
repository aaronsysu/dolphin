#include "stdafx.h"
#include "Queue.h"


namespace dolphin_common
{
	QueueElement::QueueElement(){
		_next = nullptr;
		_prev = nullptr;
		_object = nullptr;
		_queue = nullptr;
	}

	QueueElement::~QueueElement(){
	
	}

	QueueElementPtr QueueElement::Next(){
		return _next;
	}

	QueueElementPtr QueueElement::Prev(){
		return _prev;
	}

	Queue::Queue()
		: _length(0){
		_sentinel = std::make_shared<QueueElement>();
		_sentinel->_next = _sentinel;
		_sentinel->_prev = _sentinel;
	}

	Queue::~Queue(){

	}

	void Queue::EnQueue(QueueElementPtr object){
		if (object == nullptr){
			return;
		}
		object->_next = _sentinel->_next;
		object->_prev = _sentinel;
		_sentinel->_next->_prev = object;
		_sentinel->_next = object;
		_length++;
	}

	void Queue::Remove(QueueElementPtr object){
		if (object == nullptr){
			return;
		}
		
	}

	QueueElementPtr Queue::DeQueue(){
		QueueElementPtr element = nullptr;
		if (_length > 0){
			element = _sentinel->_prev;
			element->_prev->_next = _sentinel;
			_sentinel->_prev = element->_prev;
			_length--;
		}
		return element;
		
	}


	BlockingQueue::BlockingQueue(){

	}

	BlockingQueue::~BlockingQueue(){

	}

	QueueElementPtr BlockingQueue::DeQueueBlocking(unsigned short millisecondsTimeOut){
		
		if (_queue->GetLength() == 0)
		{
			std::unique_lock<std::mutex> autolock(_mutex);
			if (millisecondsTimeOut == 0){
				_cond.wait(autolock);
			}
			else{
				_cond.wait_for(autolock, std::chrono::milliseconds(millisecondsTimeOut));
			}
		}
		return _queue->DeQueue();
	}

	QueueElementPtr BlockingQueue::DeQueue(){
		std::unique_lock<std::mutex> autolock(_mutex);
		return _queue->DeQueue();
	}

	void BlockingQueue::EnQueue(QueueElementPtr obj){
		{
			std::unique_lock<std::mutex> autolock(_mutex);
			_queue->EnQueue(obj);
		}
		_cond.notify_all();
	}
}