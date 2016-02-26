#include "stdafx.h"
#include "MediaSession.h"
#include "FileSession.h"

MediaSession::MediaSession(std::string param)
	: _pMediaCallback(nullptr)
	, _pMediaObject(nullptr)
	, _param(param)
{
}


MediaSession::~MediaSession()
{
}

MediaSession* MediaSession::CreateMediaSession(std::string param)
{
	return new FileSession(param);
}

void MediaSession::DestroyMediaSession(MediaSession* pMediaSession)
{
	if (nullptr != pMediaSession)
	{
		delete pMediaSession;
		pMediaSession = nullptr;
	}
}

int MediaSession::Start()
{
	return DLPN_OK;
}

int MediaSession::Stop()
{
	return DLPN_OK;
}