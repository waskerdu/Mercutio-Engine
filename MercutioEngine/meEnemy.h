#pragma once
#include "meEntity.h"
#include "meMaterial.h"
#include "meNavSystem.h"
#include "meEnemyAggro.h"

class Enemy : public Entity
{
public:
	enum EnemyState
	{
		wandering,
		persuing,
		charging,
		attacking,
		fleeing
	};
	enum EnemyType
	{
		charger,
		thrower,
		bomber,
		suicide,
		gobble,
		gobble_thrower,
	};
	Material* chargerMatter;
	Material* throwerMatter;
	Material* bomberMatter;
	Material* chargerDeadMatter;
	Material* throwerDeadMatter;
	Material* bomberDeadMatter;
	EnemyType type = charger;
	EnemyState state = attacking;
	EnemyState oldState = wandering;
	bool newState = false;
	float positionWobbleRange = 20;
	EnemyAggro* enemyAggro;
	Entity* target;
	Entity* body;
	double chaseRange = 8000;
	bool alive = true;
	float speed = 350.0f;
	float avoid = 100.0f;
	float attackSpeed = 1000;
	float projectileSpeed = 1000;
	//float attackDistance = 1000;
	float attackRange = 1000;
	float persueRange = 800;
	float clock = 0.0f;
	float chargeTime = 3.0f;
	float chaseTime = 3;
	glm::vec3 oldPosition;
	NavSystem navSystem;
	Enemy();
	~Enemy();
	Entity* Copy();
	virtual void Update();
	void OnCollision(Entity* col);
	void Awake();
	void SetVelocity(glm::vec3 target, float speed);
	void Damage();
	void SetType(EnemyType newType);
};

