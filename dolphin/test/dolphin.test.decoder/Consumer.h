#pragma once
#include <memory>
template<typename T>
class Consumer
{
public:
	Consumer(){}
	virtual ~Consumer(){}
	virtual void Push(T &buffer) = 0;
};

template<typename T>
class Producer
{
public:
	Producer()
		: m_consumer(nullptr){}
	virtual ~Producer(){}
	void Attach(std::shared_ptr<Consumer<T>> consumer)
	{
		m_consumer = consumer;
	}
protected:
	void PushToConsumer(T &buffer)
	{
		if (m_consumer != nullptr)
		{
			m_consumer->Push(buffer);
		}
	}
private:
	std::shared_ptr<Consumer<T>> m_consumer;
};