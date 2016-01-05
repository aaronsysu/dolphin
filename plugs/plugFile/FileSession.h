#pragma once
#include "MediaSession.h"
#include <thread>
#include <mutex>
#include <condition_variable>
class FileSession :
	public MediaSession
{
public:
	FileSession(std::string param);
	~FileSession();
	int Start();
	int Stop();
private:
	void _Run();
	FILE* _videoFile;
	std::thread _engine;
	std::condition_variable _fileEvent;
	std::mutex _fileMutex;
	bool _stopFlag;
	unsigned char* _buffer;
	unsigned int   _fileTotalSize;
};

