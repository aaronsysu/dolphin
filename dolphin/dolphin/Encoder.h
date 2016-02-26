#pragma once

extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libavutil/opt.h"
}

namespace dolphin_codec
{
	class Encoder
	{
	public:
		Encoder();
		~Encoder();
	};

}