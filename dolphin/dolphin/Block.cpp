#include "stdafx.h"
#include "Block.h"
#include "Utility.h"

namespace dolphin_storage
{
#define     MAX_FILE_SIZE_M				20
#define     MAX_FILE_SIZE               (MAX_FILE_SIZE_M<<20)

	Block::Block()
		: _blockFileHandle(INVALID_HANDLE_VALUE)
	{
	}


	Block::~Block()
	{
	}

	int Block::Create(const std::string fileName)
	{
		using namespace dolphin_common;
		_fileName = fileName;
		_blockFileHandle = DLPN_OpenFile(fileName);
		if (_blockFileHandle == nullptr)
		{
			int iError = DLPN_FileGetLastError();
			return BLOCK_FILE_OPEN_ERROR;
		}
		DWORD dwNumOfByteWirtten = 0;
		DLPN_SeekFile(_blockFileHandle, MAX_FILE_SIZE - 1);
		DLPN_WriteFile(_blockFileHandle, (unsigned char*)"\0", 1);

		BLOCK_FILE_HEADER blockHeader = { 0 };
		blockHeader.magicNum = 0x1EF10CB1;
		DLPN_SeekFile(_blockFileHandle, 0);
		DLPN_WriteFile(_blockFileHandle, (unsigned char*)&blockHeader, sizeof(BLOCK_FILE_HEADER));

		return BLOCK_FILE_SUCCESS;
	}

	int Block::Delete()
	{
		dolphin_common::DLPN_DeleteFile(_fileName);
		return BLOCK_FILE_SUCCESS;
	}

	int Block::Open(const std::string fileName)
	{
		return BLOCK_FILE_SUCCESS;
	}

	int Block::Close()
	{
		dolphin_common::DLPN_CloseFile(_blockFileHandle);
		return BLOCK_FILE_SUCCESS;
	}

	int Block::Write(dolphin_common::Frame::Ptr frame)
	{
		return BLOCK_FILE_SUCCESS;
	}

	int Block::Read()
	{
		return BLOCK_FILE_SUCCESS;
	}

	int Block::ReadNextFrame()
	{
		return BLOCK_FILE_SUCCESS;
	}

}