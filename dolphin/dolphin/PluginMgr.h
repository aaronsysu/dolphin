#pragma once
#include "PlugItem.h"
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
		PlugItem* GetPlug(std::string tag){
			auto it = plugItems.find(tag);
			if (it != plugItems.end()){
				return &it->second;
			}
			return nullptr;
		}
		
		static PluginMgr* Get(){
			static PluginMgr plugMgr;
			return &plugMgr;
		}

	private:
		std::map<std::string, PlugItem> plugItems;
		std::string plugConfigFilePath;
	};
}
