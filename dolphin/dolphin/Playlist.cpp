#include "stdafx.h"
#include "Playlist.h"


namespace dolphin_media
{
	Playlist::Playlist()
	{
	}

	Playlist::Playlist(unsigned int max_items, int target_duration) :
		playlistitems(max_items),
		mediasequence(1),
		targetduration(target_duration)
	{
	}

	Playlist::~Playlist()
	{
	}

	void Playlist::AppendItem(const std::string& filename)
	{
		m_files.push_back(filename);
		while (m_files.size() > playlistitems)
		{
			m_files.pop_front();
		}
	}

	bool Playlist::UpdateLivePlaylist(const std::string& filename)
	{
		std::string m3u8file(filename);
		std::string m3u8file_tmp(m3u8file + ".tmp");
		FILE* f = nullptr;
		fopen_s(&f, m3u8file_tmp.c_str(), "w");
		if (!f)
		{
			return false;
		}
		fprintf(f, "#EXTM3U\n");
		fprintf(f, "#EXT-X-TARGETDURATION:%d\n", targetduration);
		fprintf(f, "#EXT-X-MEDIA-SEQUENCE:%d\n", mediasequence);
		for (auto fiter = m_files.begin(); fiter != m_files.end(); ++fiter)
		{
			fprintf(f, "#EXTINF:%d,\n%s\n", targetduration, (*fiter).c_str());
		}
		fclose(f);
		int iError = rename(m3u8file_tmp.c_str(), m3u8file.c_str());
		if(iError != 0)
		{
			return false;
		}

		if (m_files.size() >= playlistitems)
			mediasequence++;
		return true;
	}
}