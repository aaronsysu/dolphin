#pragma once
#include "Producer.h"
namespace dolphin_media
{
	class StreamProcducer :
		public dolphin_base::Producer
	{
	public:
		StreamProcducer(std::string param);
		~StreamProcducer();
		void Start();
		void Stop();
	private:
		void OnMedia(unsigned char* buffer, unsigned int bufferSize);
		std::string _plugTag;

		void* _mediaHandle;
	};

}