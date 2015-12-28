#include "stdafx.h"
#include "PlugItem.h"


namespace dolphin_plug{

	PlugItem::PlugItem(){
	}


	PlugItem::~PlugItem(){
	}

	int PlugItem::MediaOpen(std::string &mediaSession, OnMediaHandler fn){
		_mediaFunc = fn;
		return 0;
	}

	int PlugItem::MediaStart(std::string mediaSession, std::string param){
		return 0;
	}

	int PlugItem::MediaStop(std::string mediaSession){
		return 0;
	}

	int PlugItem::MediaClose(std::string mediaSession){
		return 0;
	}

}