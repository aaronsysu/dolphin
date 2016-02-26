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
		Frame(unsigned char* buffer, unsigned int bufferSize);
		~Frame();
		unsigned char* GetFrameBuf(){ return _buffer; }
		unsigned int GetFrameSize(){ return _bufferSize; }
		frame_type GetFrameType();
		encode_type GetEncodeType();
		bool IsKeyFrame(){ return _isKeyFrame; }
		typedef std::shared_ptr<Frame> Ptr;
	private:
		unsigned char*	_buffer;
		unsigned int	_bufferSize;
		unsigned char*  _metaData;
		unsigned int	_metaSize;
		bool			_isKeyFrame;
		int				_width;
		int				_length;
		frame_type		_frameType;
		encode_type		_encodeType;
		unsigned long   _timeStamp;
	};
}
