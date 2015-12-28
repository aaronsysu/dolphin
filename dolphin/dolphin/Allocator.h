#pragma once
#define _OS_MEMORY

class Allocator
{
public:
	Allocator();
	~Allocator();
	char* Alloc(unsigned int size);
	void Free(char* p);
private:
};

