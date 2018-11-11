#pragma once
#include <map>
#include <vector>
#include <string>

class MemoryManager
{
	std::map<std::string, std::vector<void*>*> pools;
public:
	MemoryManager();
	~MemoryManager();
	void* New(void* ent);
	void Copy(void* source, void* dest);
};

