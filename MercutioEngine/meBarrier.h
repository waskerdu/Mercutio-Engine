#pragma once
#include "meEntity.h"
class Barrier :
	public Entity
{
public:
	Barrier();
	~Barrier();
	void OnCollision(Entity* ent);
	Entity* Copy()
	{
		Barrier* copy = new Barrier(dynamic_cast<const Barrier&>(*this));
		DeepCopy(this, copy);
		return copy;
	}
};

