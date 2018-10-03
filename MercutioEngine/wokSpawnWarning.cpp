#include "stdafx.h"
#include "wokSpawnWarning.h"


SpawnWarning::SpawnWarning()
{
}


SpawnWarning::~SpawnWarning()
{
}

Entity* SpawnWarning::Copy()
{
	//copy creates a new object based on another object and returns it. sub classes will write their own version
	SpawnWarning* copy = new SpawnWarning(*this);
	DeepCopy(this, copy);
	return copy;
}

void SpawnWarning::Update()
{
	clock += (float)deltaTime;
	if (clock > spawnDelay)
	{
		//do stuff
		GetChild(0)->SetAwake(true);
		GetChild(0)->transform.Rotate(glm::vec3(0));
		GetChild(0)->SetParent(nullptr);
		children.clear();
		SetAwake(false);
		return;
	}
	transform.RotateRelative(glm::vec3(0, 0, maxSpinSpeed*clock*deltaTime / spawnDelay));
}
