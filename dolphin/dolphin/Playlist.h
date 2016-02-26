#pragma once
#include <string>
#include <list>
namespace dolphin_media
{
	class Playlist
	{
	public:
		Playlist(unsigned int max_items, int target_duration);
		virtual ~Playlist();
	public:

		size_t GetMaxItems() const { return playlistitems; }

		void AppendItem(const std::string& filename);

		bool UpdateLivePlaylist(const std::string& filename);

	protected:
		Playlist();

	private:
		unsigned int playlistitems;
		std::list<std::string> m_files;
		int mediasequence;
		int targetduration;
	};

}