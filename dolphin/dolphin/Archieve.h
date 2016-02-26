#pragma once
#include <vector>
#include "Block.h"

namespace dolphin_storage
{
	class Archieve
	{
	public:
		Archieve();
		~Archieve();
		static Archieve* Get(){
			static Archieve instance;
			return &instance;
		}

		int CreateArchive(__int64 archiveSize);
		int RemoveArchive();
		int GetBlock(Block& block);
	private:
		std::vector<Block> _blocks;
	};
}
