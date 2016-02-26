#include "stdafx.h"
#include "RecordProducer.h"
#include "Engine.h"
#include "Archieve.h"

namespace dolphin_storage
{
	RecordProducer::RecordProducer(std::string param)
		: dolphin_base::Producer(param)
		, _stopFlag(false)
	{
	}


	RecordProducer::~RecordProducer()
	{
	}

	void RecordProducer::Start()
	{
		Producer::Start();

		_stopFlag = false;

		dolphin_base::Engine::Get()->PostTask([this](void* param){
			Run();
		});
	}

	void RecordProducer::Stop()
	{
		Producer::Stop();
		_stopFlag = true;
	}

	void RecordProducer::Run()
	{
		//TODO:获取Block，读取Block数据
		Block bk;
		int iError = Archieve::Get()->GetBlock(bk);
		if (iError != 0)
		{
			return;
		}
		bk.Read();

		if (!_stopFlag)
		{
			dolphin_base::Engine::Get()->PostTask([this](void* param){
				Run();
			});
		}
	}
}