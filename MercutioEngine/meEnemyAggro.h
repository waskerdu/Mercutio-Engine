#pragma once
#include "meEntity.h"
#include <set>
class EnemyAggro :
	public Entity
{
public:
	//Entity* target;
	std::set<Entity*> targetsRef;
	std::vector<Entity*> targets;
	EnemyAggro();
	~EnemyAggro();
	void OnCollision(Entity* collider);
	Entity* Copy();
	void Render(glm::mat4* matrix){}
};

