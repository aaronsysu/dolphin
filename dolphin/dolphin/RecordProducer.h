#pragma once
#include "Producer.h"
namespace dolphin_storage
{
	class RecordProducer :
		public dolphin_base::Producer
	{
	public:
		RecordProducer(std::string param);
		~RecordProducer();
		void Start();
		void Stop();
	private:
		void Run();
	private:
		volatile bool _stopFlag;
	};
}