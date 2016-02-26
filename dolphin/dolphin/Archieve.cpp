#include "stdafx.h"
#include "Archieve.h"

namespace dolphin_storage
{
	Archieve::Archieve()
	{
	}


	Archieve::~Archieve()
	{
	}

	int Archieve::CreateArchive(__int64 archiveSize)
	{
		std::shared_ptr<Block> newBlockFile = std::make_shared<Block>();
		newBlockFile->Create(L"test.dat");
		return 0;
	}

	int Archieve::RemoveArchive()
	{
		return 0;
	}

	int Archieve::GetBlock(Block& block)
	{
		return 0;
	}
}