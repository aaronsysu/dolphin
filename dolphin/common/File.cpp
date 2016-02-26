#include "stdafx.h"
#include "File.h"

namespace dolphin_common
{
	File::File(std::string dir)
		: _dir(dir)
	{
#ifdef WIN32
		_bIsDirectory = IsDirectory();
		if (_bIsDirectory || dir.empty())
		{
			_dir.append("*");
			_fileHandle = FindFirstFileA(_dir.c_str(), &_fileData);
			if (_fileHandle == INVALID_HANDLE_VALUE)
			{
				if (GetLastError() != ERROR_NO_MORE_FILES)
				{
					//Hadle Error
				}
			}
			else
			{
				_current = _fileData.cFileName;
				if (_current == "." || _current == "..")
					Next();
			}
		}

#endif
	}


	File::~File()
	{
#ifdef WIN32
		if (_fileHandle != INVALID_HANDLE_VALUE)
			FindClose(_fileHandle);
#endif
	}

	void File::Remove()
	{
#ifdef WIN32
		if (_bIsDirectory)
		{
			if (!RemoveDirectoryA(_dir.c_str()))
			{
				//Handle Remove Error
			}
		}
		else
		{
			if (!DeleteFileA(_dir.c_str()))
			{
				//Handle Remove Error
			}
		}
#endif
	}

	void File::Rename(std::string newName)
	{
#ifdef WIN32
		if (MoveFileA(_dir.c_str(), newName.c_str()) == 0)
		{
			//Handle Remove Error
		}
#endif
	}

	bool File::IsDirectory() const
	{
#ifdef WIN32
		DWORD attr = GetFileAttributesA(_dir.c_str());
		if (attr == 0xFFFFFFFF)
		{
			return false;
		}
		return (attr & FILE_ATTRIBUTE_DIRECTORY) != 0;
#endif
	}

	void File::GetFiles(std::vector<std::string> &files)
	{
		if (_current.empty())
		{
			return;
		}
		std::string nextFile;
		files.push_back(_current);
		while (true)
		{
			nextFile = Next();
			if (nextFile == "." || nextFile == ".." || nextFile.empty())
			{
				break;
			}
			files.push_back(nextFile);
		}
	}

	const std::string& File::Next()
	{
		do
		{
			if (FindNextFileA(_fileHandle, &_fileData) != 0)
				_current = _fileData.cFileName;
			else
				_current.clear();
		} while (_current == "." || _current == "..");
		return _current;
	}

}