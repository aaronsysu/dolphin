#include "stdafx.h"
#include "PluginMgr.h"
#include <string>


namespace dolphin_plug
{
	PluginMgr::PluginMgr()
		: _plugConfigFilePath("config.ini")
	{
	}


	PluginMgr::~PluginMgr()
	{
	}

	void PluginMgr::LoadPlugs()
	{
		Plugin plugin;
		plugin.Init();
		_plugins["RTSP"] = plugin;
	}

	void PluginMgr::UnloadPlugs()
	{
		for (auto it : _plugins)
		{
			it.second.UnInit();
		}
	}
}