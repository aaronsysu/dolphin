#pragma once
#include <array>
#include <memory>
struct MediaSample
{
	//data before decoding
	typedef std::shared_ptr<MediaSample> Ptr;
	unsigned char* buffer;
	unsigned int   bufferSize;
	//data after decoding
	std::array<unsigned char*, 3> planes;
	std::array<size_t, 3> pitches;
	MediaSample()
	{
		buffer = nullptr;
		bufferSize = 0;
	}
	~MediaSample()
	{
		if (buffer)
		{
			delete[] buffer;
			bufferSize = 0;
		}
	}
};