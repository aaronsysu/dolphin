#pragma once
#include <string>
#include <map>
#include "FramePtr.h"
namespace dolphin_storage
{
#define BLOCK_FILE_SUCCESS		0
#define BLOCK_FILE_OPEN_ERROR	1
	//Block文件头
	typedef struct tagBLOCK_FILE_HEADER
	{
		unsigned long magicNum;
		unsigned long sliceNum;
		unsigned long startTimeHigh;
		unsigned long startTimeLow;
		unsigned long endTimeHigh;
		unsigned long endTimeLow;
	}BLOCK_FILE_HEADER;
	//Block Slice文件头
	typedef struct tagSLICE_HEADER 
	{
		unsigned long timeHigh;
		unsigned long timeLow;
		unsigned long sliceLength;
		unsigned long fileOffset;
	}SLICE_HEADER;

	class Block
	{
	public:
		Block();
		~Block();
		int Create(const std::string fileName);
		int Close();
		int Delete();
		int Open(const std::string fileName);
		int Write(dolphin_common::Frame::Ptr frame);
		int Read();
		int ReadNextFrame();
	private:
		BLOCK_FILE_HEADER* _blockFileHeader;
		std::map<__int64, SLICE_HEADER> _slices;
		HANDLE _blockFileHandle;
		std::string _fileName;
	};
}