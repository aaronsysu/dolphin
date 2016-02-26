#include "stdafx.h"
#include "FramePtr.h"


namespace dolphin_common
{
	Frame::Frame(unsigned char* buffer, unsigned int bufferSize)
		: _buffer(buffer)
		, _bufferSize(bufferSize)
		, _metaData(nullptr)
		, _metaSize(0)
		, _isKeyFrame(false)
	{
		int nType = _buffer[4] & 0x1F;
		if (nType == 2 || nType == 7 || nType == 8 || nType == 5)
		{
			_isKeyFrame = true;
		}
	}


	Frame::~Frame()
	{
	}
}