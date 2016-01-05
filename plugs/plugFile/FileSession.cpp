#include "stdafx.h"
#include "FileSession.h"

#define FILE_SIZE  1024 * 2
FileSession::FileSession(std::string param)
	: MediaSession(param)
	, _stopFlag(false)
{
	_buffer = new unsigned char[FILE_SIZE];
	memset(_buffer, 0, FILE_SIZE);
	_fileTotalSize = FILE_SIZE;
}


FileSession::~FileSession()
{
	delete _buffer;
}

int FileSession::Start()
{
	fopen_s(&_videoFile, "test.mp4", "wb+");
	_fileTotalSize = _videoFile->_bufsiz;
	if (nullptr == _videoFile)
	{
		return DLPN_PLUG_MEDIA_START_ERROR;
	}

	std::thread tmpEngine(std::bind(&FileSession::_Run, this));
	_engine.swap(tmpEngine);

	return DLPN_OK;
}

int FileSession::Stop()
{
	_stopFlag = true;
	if (_engine.joinable())
	{
		_engine.join();
	}
	return DLPN_OK;
}

void FileSession::_Run()
{
	size_t tmpFileSizeRead = 0;
	while (!_stopFlag)
	{
		std::unique_lock<std::mutex> lock(_fileMutex);
		_fileEvent.wait_for(lock, std::chrono::microseconds(100));

		tmpFileSizeRead += fread(_buffer, 1, FILE_SIZE, _videoFile);
		if (tmpFileSizeRead > _fileTotalSize)
		{
			fseek(_videoFile, 0, SEEK_SET);
			continue;
		}
		fseek(_videoFile, tmpFileSizeRead, SEEK_SET);
	}
}