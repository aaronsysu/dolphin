#pragma once
#include <thread>
namespace dolphin_common
{
#define IO_STOP		0
#define IO_READ		1
#define IO_WRITE	2

	typedef struct tagIO_DATA 
	{
		int type;
		unsigned char*	buffer;
		unsigned int	bufferSize;
	}IO_DATA, *LPIO_DATA;

	class AsyncFile
	{
	public:
		AsyncFile();
		~AsyncFile();
		void Init();
		void UnInit();
		void Write(unsigned char* buffer, unsigned int bufferSize);
		void Read(unsigned char* buffer, unsigned int bufferSize);
	private:
		void Run();
	private:
		HANDLE _fileHandle;
		std::thread _worker;
	};
}