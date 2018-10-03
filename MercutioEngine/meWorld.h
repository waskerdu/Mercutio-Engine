#pragma once
#include "meEntity.h"
#include "meCamera.h"
#include "meRandom.h"

//contains world state

class World
{
public:
	std::vector<int> controllerOrder;
	std::vector<Camera*> cameras;
	std::vector<Entity*> entities;
	std::vector<Entity*> prototypes;
	int numLayers = 10;
	Random random;
	std::vector<std::vector<Entity*>> layers;
	World()
	{
		entities = std::vector<Entity*>();
		for (int i = 0; i < numLayers; i++)
		{
			layers.push_back(std::vector<Entity*>());
		}
	}

	~World()
	{

	}

	Entity &operator[](int ind)
	{
		return *entities[ind];
	}

	void AddCamera(Camera* ent)
	{
		cameras.push_back(ent);
		ent->random = &random;
	}

	void AddEntity(Entity* ent) 
	{
		entities.push_back(ent);
		int layer = (int)ent->layer;
		if (layer > -1 && layer < numLayers)
		{
			layers[layer].push_back(ent);
		}
		ent->random = &random;
	}

	void AddPrototype(Entity* ent)
	{
		prototypes.push_back(ent);
		ent->random = &random;
		ent->SetDeleteStatus(false);
	}

	Entity GetEnt(int ind)
	{
		return *entities[ind];
	}

	void RebuildLayers()
	{
		for (uint32_t i = 0; i < layers.size(); i++)
		{
			layers[i].clear();
		}
		for (uint32_t i = 0; i < entities.size(); i++)
		{
			Entity* ent = entities[i];
			int layer = (int)ent->layer;
			if (layer > -1 && layer < numLayers)
			{
				layers[layer].push_back(ent);
			}
		}
	}

};