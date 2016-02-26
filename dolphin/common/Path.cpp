#include "stdafx.h"
#include "Path.h"


namespace dolphin_common
{
	Path::Path(const std::string& path)
	{
	}


	Path::~Path()
	{
	}

	std::string Path::GetCurPath()
	{
		std::string result;
		char buffer[MAX_PATH];
		DWORD n = GetCurrentDirectoryA(sizeof(buffer), buffer);
		if (n > 0 && n < sizeof(buffer))
		{
			result.append(buffer, n);
			if (result[n - 1] != '\\')
				result.append("\\");
		}
		return result;
	}
}