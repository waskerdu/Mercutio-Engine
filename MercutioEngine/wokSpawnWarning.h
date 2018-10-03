#pragma once
#include "meEntity.h"
class SpawnWarning :
	public Entity
{
public:
	float maxSpinSpeed = 60.0f;
	float clock = 0.0f;
	float spawnDelay = 2.0f;
public:
	SpawnWarning();
	~SpawnWarning();
	void Update();
	Entity* Copy();
};

