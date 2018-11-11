#include "stdafx.h"
#include "meMemoryManager.h"
#include <typeinfo>
#include <iostream>
#include "meEntity.h"

MemoryManager::MemoryManager()
{
}


MemoryManager::~MemoryManager()
{
	std::map<std::string, std::vector<void*>*>::iterator it;

	for (it = pools.begin(); it != pools.end(); it++)
	{
		for (size_t i = 0; i < it->second->size(); i++)
		{
			delete(it->second->at(i));
		}
		delete it->second;
	}
}

void MemoryManager::Copy(void* _source, void* _dest)
{
	//a deep copy method 
	Entity* source = (Entity*)_source;
	Entity* dest = (Entity*)_dest;
	//*dest = *source;
	dest->children.clear();
	/*for (size_t i = 0; i < source->children.size(); i++)
	{
		dest->children.push_back((Entity*)New(source->children[i]));
		dest->children.back()->parent = dest;
	}/**/
}

void* MemoryManager::New(void* e)
{
	Entity* ent = (Entity*)e;
	std::string name = typeid(*ent).name();
	if (pools.count(name) == 0)
	{
		//create a new pool
		pools[name] = new std::vector<void*>();
	}
	//get a free object if avalible. if not 
	//allocate a new object in the pool, copy e to it, and return it
	Entity* tempEnt;
	for (size_t i = 0; i < pools[name]->size(); i++)
	{
		tempEnt = (Entity*)pools[name]->at(i);
		if (tempEnt->freed)
		{
			//copy into tempEnt and return it
			tempEnt->freed = false;
			*tempEnt = *ent;
			//Copy(ent, tempEnt);
			//std::cout << "reused\n";
			return tempEnt;
		}
	}
	tempEnt = ent->Copy();
	pools[name]->push_back(tempEnt);
	std::cout << "created new\n";
	return tempEnt;
}
