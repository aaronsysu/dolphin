#pragma once
#include <memory>
namespace dolphin_common
{
	typedef enum enumENCODE_TYPE
	{
		frame_h264,
		frame_mpeg4,
		frame_mpeg2
	}encode_type;

	typedef enum enumFRAME_TYPE
	{
		iframe,
		pframe,
		bframe
	}frame_type;

	class Frame
	{
	public:
		Frame();
		~Frame();
		void* GetFrameBuf();
		void* GetFrameSize();
		frame_type GetFrameType();
		encode_type GetEncodeType();
		typedef std::shared_ptr<Frame> Ptr;
	private:
		unsigned char*	_buffer;
		unsigned int	_bufferSize;
		unsigned char*  _metaData;
		unsigned int	_metaSize;
		int				_width;
		int				_length;
		frame_type		_frameType;
		encode_type		_encodeType;
		unsigned long   _timeStamp;
	};
}
