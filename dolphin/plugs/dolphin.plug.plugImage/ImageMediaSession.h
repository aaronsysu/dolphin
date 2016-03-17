#pragma once
#include "../MediaSession.h"
class ImageMediaSession
	: public MediaSession
{
public:
	ImageMediaSession();
	~ImageMediaSession();
	virtual void Open(const std::string param);
	virtual void Start();
	virtual void Stop();
	virtual void Close();
};

