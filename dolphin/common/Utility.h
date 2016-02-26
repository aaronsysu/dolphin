#pragma once
#include <string>
#include <map>
namespace dolphin_common
{
	typedef void* DLPN_HANDLE;

	DLPN_HANDLE DLPN_OpenFile(std::string fileName);
	unsigned int DLPN_ReadFile(DLPN_HANDLE fileHandle, unsigned char* buffer, unsigned int bufferSize);
	unsigned int DLPN_WriteFile(DLPN_HANDLE fileHandle, unsigned char* buffer, unsigned int bufferSize);
	unsigned int DLPN_SeekFile(DLPN_HANDLE fileHandle, unsigned int offset);
	unsigned int DLPN_CloseFile(DLPN_HANDLE fileHandle);
	unsigned int DLPN_DeleteFile(std::string fileName);
	int DLPN_FileGetLastError();

	class Utility
	{
	public:
		Utility();
		~Utility();
		static std::wstring StringToWString(const std::string str);
		static std::string WStringToString(const std::wstring wstr);
	};
}
