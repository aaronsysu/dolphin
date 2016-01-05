#pragma once
#include "Plug.h"
#include <string>

class MediaSession
{
public:
	MediaSession(std::string param);
	~MediaSession();
	static MediaSession* CreateMediaSession(std::string param);
	static void DestroyMediaSession(MediaSession* pMediaSession);
	void SetMediaCallback(funcRealCallBack lpCallback, void* pObject){
		_pMediaCallback = lpCallback;
		_pMediaObject = pObject;
	}
	virtual int Start();
	virtual int Stop();
private:
	funcRealCallBack _pMediaCallback;
	void* _pMediaObject;
	std::string _param;
};

