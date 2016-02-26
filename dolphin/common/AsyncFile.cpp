#include "stdafx.h"
#include "AsyncFile.h"


namespace dolphin_common
{
	AsyncFile::AsyncFile()
	{
	}

	AsyncFile::~AsyncFile()
	{
	}

	void AsyncFile::Init()
	{
		_fileHandle = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
		if (_fileHandle == NULL)
		{
			return;
		}
		_worker.swap(std::thread([=]{
			Run();
		}));
	}

	void AsyncFile::UnInit()
	{
		LPIO_DATA pIOData = new IO_DATA;
		memset(pIOData, 0, sizeof(IO_DATA));
		pIOData->type = IO_STOP;
		pIOData->buffer = NULL;
		pIOData->bufferSize = 0;

		unsigned int nNumberOfBytesTransfered = 0;
		PostQueuedCompletionStatus(_fileHandle, nNumberOfBytesTransfered, 0, (LPOVERLAPPED)pIOData);
		_worker.join();
	}

	void AsyncFile::Write(unsigned char* buffer, unsigned int bufferSize)
	{
		LPIO_DATA pIOData = new IO_DATA;
		memset(pIOData, 0, sizeof(IO_DATA));
		pIOData->type = IO_WRITE;
		pIOData->buffer = buffer;
		pIOData->bufferSize = bufferSize;

		unsigned int nNumberOfBytesTransfered = 0;
		PostQueuedCompletionStatus(_fileHandle, nNumberOfBytesTransfered, 0, (LPOVERLAPPED)pIOData);

	}

	void AsyncFile::Read(unsigned char* buffer, unsigned int bufferSize)
	{
		LPIO_DATA pIOData = new IO_DATA;
		memset(pIOData, 0, sizeof(IO_DATA));
		pIOData->type = IO_READ;
		pIOData->buffer = buffer;
		pIOData->bufferSize = bufferSize;

		unsigned int nNumberOfBytesTransfered = 0;
		PostQueuedCompletionStatus(_fileHandle, nNumberOfBytesTransfered, 0, (LPOVERLAPPED)pIOData);
	}

	void AsyncFile::Run()
	{
		DWORD dwTransCount = 0;
		HANDLE hIOFd = NULL;
		IO_DATA* pIOData = NULL;
		BOOL bRet = FALSE;
		for (;;)
		{
			bRet = GetQueuedCompletionStatus(_fileHandle, &dwTransCount, (PULONG_PTR)&hIOFd, (LPOVERLAPPED *)&pIOData, INFINITE);
			if (bRet)
			{
				if (pIOData->type == IO_READ)
				{
				}
				else if (pIOData->type == IO_WRITE)
				{
				}
				else if (pIOData->type == IO_STOP)
				{
					break;
				}
				delete pIOData;
			}
		}
	}

}