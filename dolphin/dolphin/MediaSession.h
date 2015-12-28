#pragma once
#include <string>
namespace dolphin_media
{
	class MediaSession
	{
	public:
		MediaSession(std::string param);
		~MediaSession();
		int Start();
		int Stop();
	};
}
