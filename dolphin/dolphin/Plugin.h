#pragma once
#include "./../plugs/Plug.h"
#include <string>
#include <functional>
namespace dolphin_plug
{
	typedef std::function<void(unsigned char*, unsigned int)> onMediaFn;
	class Plugin
	{
	public:
		Plugin();
		~Plugin();
	public:
		bool Init();
		void UnInit();
	public:
		int MediaOpen(std::string param, onMediaFn fn, void** mediaHandle);
		int MediaClose(void* mediaHandle);
		int MediaStart(void* mediaHandle);
		int MediaStop(void* mediaHandle);
	private:
		bool LoadPlugin(std::wstring pluginPath);
		void LoadInterface();
		static void WINAPI MediaCallBack(unsigned char* pBuffer, int nBuffer, void* pObject);
	private:
		std::wstring _pluginPath;
		HMODULE _pluginModule;

		onMediaFn _onMedia;

		_funcMediaOpen _MediaOpen;
		_funcMediaSetCallback _MediaSetCallback;
		_funcMediaStart _MediaStart;
		_funcMediaStop _MediaStop;
		_funcMediaClose _MediaClose;
	};

}