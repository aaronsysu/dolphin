#pragma once
#include <string>
#include <functional>

namespace dolphin_plug
{
	typedef std::function<bool(const std::string&, void*)> OnMediaHandler;
	class PlugItem
	{
	public:
		PlugItem();
		~PlugItem();
		int Init();
		void UnInit();
		const std::string& GetTag(){
			return _tag;
		}

		int MediaOpen(std::string &mediaSession, OnMediaHandler fn);
		int MediaStart(std::string mediaSession, std::string param);
		int MediaStop(std::string mediaSession);
		int MediaClose(std::string mediaSession);
	private:
		//²å¼þ±êÇ©
		std::string _tag;
		OnMediaHandler _mediaFunc;
	};
}