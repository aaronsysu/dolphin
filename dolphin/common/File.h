#pragma once
#include <string>
#include <vector>

#ifdef WIN32
#include <windows.h>
#endif

namespace dolphin_common
{
	class File
	{
	public:
		File(std::string dir);
		~File();
		void Remove();
		void Rename(std::string newName);
		bool IsDirectory() const;
		void GetFiles(std::vector<std::string> &files);
		std::string Path(){ return _dir; }
	private:
		const std::string& Next();
	private:
		std::string _dir;
		std::vector<std::string> _files;
		bool _bIsDirectory;
#ifdef WIN32
		HANDLE _fileHandle;
		WIN32_FIND_DATAA _fileData;
#endif
		std::string _current;
	};
}

