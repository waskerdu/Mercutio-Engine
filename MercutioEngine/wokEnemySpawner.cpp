#include "stdafx.h"
#include "wokEnemySpawner.h"
#include "wokSpawnWarning.h"

EnemySpawner::EnemySpawner()
{
}


EnemySpawner::~EnemySpawner()
{
}

Entity* EnemySpawner::Copy()
{
	//copy creates a new object based on another object and returns it. sub classes will write their own version
	EnemySpawner* copy = new EnemySpawner(*this);
	DeepCopy(this, copy);
	return copy;
}

void EnemySpawner::Awake()
{
	//Wave();
}

void EnemySpawner::Wave()
{
	Enemy* newEnemy;
	SpawnWarning* newWarning;

	if (numberOfWaves == 0) { return; }
	else { numberOfWaves--; }
	float totalProb;
	float roll;
	for (unsigned int i = 0; i < waveSize; i++)
	{
		newWarning = dynamic_cast<SpawnWarning*>(spawnWarning->Copy());
		totalProb = chargeProb + throwProb + bombProb;
		if (totalProb == 0.0f)
		{
			newEnemy = dynamic_cast<Enemy*>(charger->Copy());
		}
		else
		{
			roll = (float)RandReal() * totalProb;
			if (roll < chargeProb)
			{
				newEnemy = dynamic_cast<Enemy*>(charger->Copy());
			}
			else if (roll < chargeProb + throwProb)
			{
				newEnemy = dynamic_cast<Enemy*>(thrower->Copy());
			}
			else
			{
				newEnemy = dynamic_cast<Enemy*>(bomber->Copy());
			}
		}
		//newEnemy = dynamic_cast<Enemy*>(bomber->Copy());
		/*if (RandReal() < throwerProb)
		{
			newEnemy = dynamic_cast<Enemy*>(thrower->Copy());
		}
		else
		{
			newEnemy = dynamic_cast<Enemy*>(charger->Copy());
		}/**/
		newEnemy->transform.position.x = (float)RandReal()*radius * 2 - radius;
		newEnemy->transform.position.y = (float)RandReal()*radius * 2 - radius;
		newEnemy->transform.position += transform.position;
		newEnemy->enemyAggro = dynamic_cast<EnemyAggro*>(newEnemy->children[0]);
		newEnemy->SetAwake(false);
		newWarning->transform.position = newEnemy->transform.position;
		newWarning->AddChild(newEnemy);
		initQueue.push_back(newWarning);
		spawnedEnemies.push_back(newEnemy);
		initQueue.push_back(newEnemy);
		spawnWarnings.push_back(newWarning);
	}
	waveSize += waveIncrement;
}