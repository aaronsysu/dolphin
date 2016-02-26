#pragma once
#define _OS_MEMORY

namespace dolphin_common
{
	class Allocator
	{
	public:
		Allocator();
		~Allocator();
		char* Alloc(unsigned int size);
		void Free(char* p);
	private:
	};

}