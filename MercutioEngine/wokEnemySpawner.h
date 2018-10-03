#pragma once
#include "meEntity.h"
#include "meEnemy.h"
class EnemySpawner : public Entity
{
public:
	Enemy* charger;
	Enemy* thrower;
	Enemy* bomber;
	float throwProb = 0.0f;
	float chargeProb = 0.0f;
	float bombProb = 0.0f;
	Entity* spawnWarning;
	std::vector<Entity*> spawnWarnings;
	std::vector<Entity*> spawnedEnemies;
	unsigned int waveSize = 1;
	unsigned int waveIncrement = 1;
	int numberOfWaves = 2;
	//float throwerProb = 0.5f;
	float radius = 1000.0f;
private:
public:
	void Wave();
	Entity* Copy();
	EnemySpawner();
	void Awake();
	~EnemySpawner();
};

