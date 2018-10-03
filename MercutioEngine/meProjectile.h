#pragma once
#include "meEntity.h"
class Projectile :
	public Entity
{
public:
	int health = 1;
	float chargeRate = 1.0f;
	float speed = 0.0f;
	bool explodes = false;
	float explodeScale = 6.0f;
	float explodeTime = 0.5f;
	float explodeClock = 0.0f;
	Material* explodeMatter;
	enum State
	{
		active,
		dead,
		exploding,
		none,
	};
	State state = active;
	State lastState = none;
	std::string targetTag = "bad";
	bool alive = true;
	Projectile();
	~Projectile();
	Entity* staticP;
	void OnCollision(Entity* collider);
	Entity* Copy();
	void Update();
};

