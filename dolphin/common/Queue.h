#pragma once
#include <mutex>
#include <memory>
#include <condition_variable>

namespace dolphin_common
{
	template <typename T>
	class Queue;

	template <typename T>
	class QueueElement
	{
	public:
		QueueElement(){
			_next = nullptr;
			_prev = nullptr;
			_object = nullptr;
			_queue = nullptr;
		}
		~QueueElement(){}
		typedef std::shared_ptr<QueueElement<T>> QueueElementPtr;

		static std::shared_ptr<QueueElement<T>> CreateNewElem(){
			return std::make_shared<QueueElement<T>>();
		}
		QueueElement<T>* Next(){
			return _next;
		}
		QueueElement<T>* Prev(){
			return _prev;
		}
		void SetObj(T& obj){
			_object = obj;
		}
		T GetObj(){
			return _object;
		}
		friend class Queue < T > ;
	private:

		std::shared_ptr<QueueElement<T>>	_next;
		std::shared_ptr<QueueElement<T>>	_prev;
		std::shared_ptr<Queue<T>>			_queue;
		T				_object;
	};

	template <typename T>
	class Queue
	{
	public:
		Queue(){
			_length = 0;
			_sentinel = std::make_shared<QueueElement<T>>();
			_sentinel->_next = _sentinel;
			_sentinel->_prev = _sentinel;
		}
		~Queue(){}

		void EnQueue(std::shared_ptr<QueueElement<T>> object){
			if (object == nullptr){
				return;
			}
			object->_next = _sentinel->_next;
			object->_prev = _sentinel;
			_sentinel->_next->_prev = object;
			_sentinel->_next = object;
			_length++;
		}
		std::shared_ptr<QueueElement<T>> DeQueue(){
			std::shared_ptr<QueueElement<T>> element = nullptr;
			if (_length > 0){
				element = _sentinel->_prev;
				element->_prev->_next = _sentinel;
				_sentinel->_prev = element->_prev;
				_length--;
			}
			return element;
		}

		std::shared_ptr<QueueElement<T>>	GetHead() { if (_length > 0) return _sentinel->_prev; return nullptr; }
		std::shared_ptr<QueueElement<T>>	GetTail() { if (_length > 0) return _sentinel->_next; return nullptr; }
		unsigned int	GetLength() { return _length; }

		void Remove(QueueElement<T> object){
			if (object == nullptr){
				return;
			}
		}
	private:
		unsigned int	_length;
		std::shared_ptr<QueueElement<T>> _sentinel;
	};

	template <typename T>
	class BlockingQueue
	{
	public:
		BlockingQueue(){
			_queue = std::make_shared<Queue<T>>();
		}

		~BlockingQueue(){}

		std::shared_ptr<QueueElement<T>> DeQueueBlocking(unsigned short millisecondsTimeOut = 0){

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

		QueueElement<T> DeQueue(){
			std::unique_lock<std::mutex> autolock(_mutex);
			return _queue->DeQueue();
		}

		void EnQueue(std::shared_ptr<QueueElement<T>> obj){
			{
				std::unique_lock<std::mutex> autolock(_mutex);
				_queue->EnQueue(obj);
			}
			_cond.notify_all();
		}

		std::shared_ptr<Queue<T>>	GetQueue()  { return _queue; }

	private:

		std::condition_variable             _cond;
		std::mutex							_mutex;
		std::shared_ptr<Queue<T>>			_queue;
	};
}
