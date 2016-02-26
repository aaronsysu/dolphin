#include "stdafx.h"
#include "Plugin.h"

#define LOG_TRACE

#define LOADPROC(module, name)  do {                                    \
	_##name = reinterpret_cast<_func##name>(GetProcAddress(module, #name));  \
	if (NULL == _##name) LOG_TRACE("_%s is NULL", #name);\
} while (0)

namespace dolphin_plug
{
	Plugin::Plugin()
	{
		_pluginModule = nullptr;
		_MediaOpen = nullptr;
		_MediaSetCallback = nullptr;
		_MediaStart = nullptr;
		_MediaStop = nullptr;
		_MediaClose = nullptr;
	}


	Plugin::~Plugin()
	{
	}

	bool Plugin::Init()
	{
		bool bResult = LoadPlugin(std::wstring(L"./plugin/dolphin.plug.plugRtsp.dll"));
		if (!bResult)
		{
			return false;
		}
		LoadInterface();
		return true;
	}

	void Plugin::UnInit()
	{
		FreeLibrary(_pluginModule);
		_pluginModule = nullptr;
	}

	bool Plugin::LoadPlugin(std::wstring pluginPath)
	{
		_pluginPath = pluginPath;
		_pluginModule = ::LoadLibraryEx(_pluginPath.c_str(), NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
		if (_pluginModule != nullptr){
			return true;
		}
		return false;
	}

	void Plugin::LoadInterface()
	{
		LOADPROC(_pluginModule, MediaOpen);
		LOADPROC(_pluginModule, MediaClose);
		LOADPROC(_pluginModule, MediaSetCallback);
		LOADPROC(_pluginModule, MediaStart);
		LOADPROC(_pluginModule, MediaStop);
	}

	void Plugin::MediaCallBack(unsigned char* pBuffer, int nBuffer, void* pObject)
	{
		Plugin* plug = (Plugin*)pObject;
		plug->_onMedia(pBuffer, nBuffer);
	}

	int Plugin::MediaOpen(const std::string param, onMediaFn fn, void** mediaHandle)
	{
		int nErr = _MediaOpen(param.c_str(), mediaHandle);
		if (nErr == 0)
		{
			_MediaSetCallback(*mediaHandle, MediaCallBack, this);
			_onMedia = fn;
		}
		return nErr;
	}

	int Plugin::MediaClose(void* mediaHandle)
	{
		return _MediaClose(mediaHandle);
	}

	int Plugin::MediaStart(void* mediaHandle)
	{
		return _MediaStart(mediaHandle);
	}

	int Plugin::MediaStop(void* mediaHandle)
	{
		return _MediaStop(mediaHandle);
	}

}