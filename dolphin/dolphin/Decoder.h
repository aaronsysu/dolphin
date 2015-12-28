#pragma once
#include "FramePtr.h"
namespace dolphin_codec
{
	class Decoder
	{
	public:
		Decoder();
		~Decoder();
		virtual int DecodeFrame(dolphin_common::Frame::Ptr frame) = 0;
	};
}