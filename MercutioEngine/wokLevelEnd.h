#pragma once
#include "meEntity.h"
class LevelEnd :
	public Entity
{
	bool isOpen = false;
public:
	float radius = 100;
	Material* openMatter;
	Material* closedMatter;
	std::string nextLevel;
	bool locked = false;
public:
	LevelEnd();
	~LevelEnd();
	bool IsOpen() { return isOpen; }
	void SetOpen(bool open)
	{
		isOpen = open;
		if (isOpen) { materialPtr = openMatter; }
		else { materialPtr = closedMatter; }
	}
	Entity* Copy()
	{
		LevelEnd* ent = new LevelEnd(*this);
		DeepCopy(this, ent);
		return ent;
	}
};
