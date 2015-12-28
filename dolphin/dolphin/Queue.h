#pragma once
#include <mutex>
#include <memory>
#include <condition_variable>

namespace dolphin_common
{
	class QueueElement;
	class Queue;

	typedef std::shared_ptr<QueueElement> QueueElementPtr;
	typedef std::shared_ptr<Queue> QueuePtr;

	class QueueElement
	{
	public:
		QueueElement();
		~QueueElement();
		static QueueElementPtr CreateNewElem(){
			return std::make_shared<QueueElement>();
		}
		QueueElementPtr Next();
		QueueElementPtr Prev();
		void SetObj(void* obj){
			_object = obj;
		}
		void* GetObj(){
			return _object;
		}
	private:

		QueueElementPtr	_next;
		QueueElementPtr _prev;
		QueuePtr		_queue;
		void*			_object;

		friend class    Queue;
	};

	class Queue
	{
	public:
		Queue();
		~Queue();

		void			EnQueue(QueueElementPtr object);
		QueueElementPtr	DeQueue();

		QueueElementPtr	GetHead() { if (_length > 0) return _sentinel->_prev; return NULL; }
		QueueElementPtr	GetTail() { if (_length > 0) return _sentinel->_next; return NULL; }
		unsigned int	GetLength() { return _length; }

		void			Remove(QueueElementPtr object);
	private:
		unsigned int	_length;
		QueueElementPtr _sentinel;
	};

	class BlockingQueue
	{
	public:
		BlockingQueue();
		~BlockingQueue();

		QueueElementPtr		DeQueueBlocking(unsigned short millisecondsTimeOut = 0);
		QueueElementPtr		DeQueue();
		void				EnQueue(QueueElementPtr obj);
		QueuePtr			GetQueue()  { return _queue; }

	private:

		std::condition_variable             _cond;
		std::mutex							_mutex;
		QueuePtr							_queue;
	};
}
