#include "stdafx.h"
#include "wokPressurePlate.h"


PressurePlate::PressurePlate()
{
}


PressurePlate::~PressurePlate()
{
}


void PressurePlate::RemoveTarget(Entity* target)
{
	for (uint32_t i = 0; i < targets.size(); i++)
	{
		if (targets[i] == target)
		{
			targets.erase(targets.begin() + i);
			return;
		}
	}
	std::cout << "RemoveTarget failed, no matching target found.\n";
}


void PressurePlate::OnCollision(Entity* ent)
{
	if (ent->tags.count(activatorTag) && isDown == false) { isDown = true; }
}


void PressurePlate::Update()
{
	if (isDown && !isDownLast)
	{
		//transmit
		for each (Entity* target in targets)
		{
			target->SendMessage(message);
			//std::cout << "message sent\n";
		}
		isDown = false;
		materialPtr = downMatter;
	}
	else if (!isDown) 
	{ 
		isDownLast = false; 
		materialPtr = upMatter;
	}
}

Entity* PressurePlate::Copy()
{
	//copy creates a new object based on another object and returns it. sub classes will write their own version
	PressurePlate* copy = new PressurePlate(*this);
	DeepCopy(this, copy);
	return copy;
}