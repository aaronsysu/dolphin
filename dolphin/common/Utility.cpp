#include "stdafx.h"
#include "Utility.h"

namespace dolphin_common
{

	DLPN_HANDLE DLPN_OpenFile(std::string fileName)
	{
		FILE* file = nullptr;
		fopen_s(&file, fileName.c_str(), "wb+");
		return (DLPN_HANDLE)file;
	}

	unsigned int DLPN_ReadFile(DLPN_HANDLE fileHandle, unsigned char* buffer, unsigned int bufferSize)
	{
		return fread_s(buffer, bufferSize, 1, 1, (FILE*)fileHandle);
	}

	unsigned int DLPN_WriteFile(DLPN_HANDLE fileHandle, unsigned char* buffer, unsigned int bufferSize)
	{
		return fwrite(buffer, bufferSize, 1, (FILE*)fileHandle);
	}

	unsigned int DLPN_SeekFile(DLPN_HANDLE fileHandle, unsigned int offset)
	{
		return fseek((FILE*)fileHandle, offset, 0);
	}

	int DLPN_FileGetLastError()
	{
		return GetLastError();
	}

	unsigned int DLPN_CloseFile(DLPN_HANDLE fileHandle)
	{
		return fclose((FILE*)fileHandle);
	}

	unsigned int DLPN_DeleteFile(std::string fileName)
	{
		return remove(fileName.c_str());
	}

	Utility::Utility()
	{
	}


	Utility::~Utility()
	{
	}

	std::wstring Utility::StringToWString(const std::string str)
	{
		int nLen = (int)str.length();
		std::wstring wstr;
		wstr.resize(nLen, L' ');

		int nResult = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)str.c_str(), nLen, (LPWSTR)wstr.c_str(), nLen);

		if (nResult == 0)
		{
			return wstr;
		}

		return wstr;
	}

	std::string Utility::WStringToString(const std::wstring wstr)
	{
		std::string str;
		int nLen = (int)wstr.length();
		str.resize(nLen, ' ');

		int nResult = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)wstr.c_str(), nLen, (LPSTR)str.c_str(), nLen, NULL, NULL);

		if (nResult == 0)
		{
			return str;
		}

		return str;
	}
}