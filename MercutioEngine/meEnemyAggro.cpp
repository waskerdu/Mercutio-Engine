#include "stdafx.h"
#include "meEnemyAggro.h"


EnemyAggro::EnemyAggro()
{
}


EnemyAggro::~EnemyAggro()
{
}

void EnemyAggro::OnCollision(Entity* collider)
{
	if (collider->tags.count("hero") > 0)
	{
		//target = collider;
		if (targetsRef.count(collider) == 0)
		{
			targetsRef.insert(collider);
			targets.push_back(collider);
		}
	}
	/*if (target == nullptr)
	{
		if (collider->tags.count("hero") > 0)
		{
			//target = collider;
			if (targetsRef.count(collider) == 0)
			{
				targetsRef.insert(collider);
				targets.push_back(collider);
			}
			//std::cout << "target aquired\n";
		}
	}*/
}

Entity* EnemyAggro::Copy()
{
	//copy creates a new object based on another object and returns it. sub classes will write their own version
	EnemyAggro* copy = new EnemyAggro(*this);
	DeepCopy(this, copy);
	return copy;
}
