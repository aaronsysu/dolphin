#pragma once
namespace dolphin_stream
{
	class StreamReciever
	{
	public:
		StreamReciever();
		~StreamReciever();
	private:
		unsigned char*	_streamBuffer;
		unsigned int	_streamBufferSize;
	};
}
