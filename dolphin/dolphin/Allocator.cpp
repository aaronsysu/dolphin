#include "stdafx.h"
#include "Allocator.h"


Allocator::Allocator()
{
}


Allocator::~Allocator()
{
}

char* Allocator::Alloc(unsigned int size)
{
#if defined(_OS_MEMORY)
	return new char[size];
#endif
}

void Allocator::Free(char* p)
{
#if defined(_OS_MEMORY)
	delete [] p;
	p = nullptr;
#endif
}