#pragma once
#include "Plugin.h"
#include <map>

namespace dolphin_plug
{
	class PluginMgr
	{
	public:
		PluginMgr();
		~PluginMgr();
		void LoadPlugs();
		void UnloadPlugs();
		Plugin* GetPlug(std::string tag){
			auto it = _plugins.find(tag);
			if (it != _plugins.end()){
				return &it->second;
			}
			return nullptr;
		}
		
		static PluginMgr* Get(){
			static PluginMgr plugMgr;
			return &plugMgr;
		}

	private:
		std::map<std::string, Plugin> _plugins;
		std::string _plugConfigFilePath;
	};
}
