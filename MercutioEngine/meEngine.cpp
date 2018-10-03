#include "stdafx.h"
#include "meEngine.h"
#include "mePhysics.h"

void Engine::Reset()
{
	//clear out entities from world list unless specially marked
	//call awake on all remaining entities
	for (uint32_t i = 0; i < worldPtr->entities.size(); i++)
	{
		if (worldPtr->entities[i]->doNotDelete)
		{
			worldPtr->entities[i]->lastWakeState = false;
			worldPtr->entities[i]->Reset();
			//std::cout << "got to reset\n";
		}
		else
		{
			worldPtr->entities[i]->SetAwake(false);
		}
	}/**/
	/*for (uint32_t i = worldPtr->entities.size()-1; i > -1; i--)
	{
		Entity* ent = worldPtr->entities[i];
		if(ent->doNotDelete)
		{
			ent->lastWakeState = false;
			//std::cout << "got here\n";
			ent->Reset();
		}
		else
		{
			for (uint32_t f = ent->initQueue.size() - 1; f > -1; f--)
			{
				delete ent->initQueue[f];
			}
			delete ent;
			//std::cout << "got here\n";
			worldPtr->entities.erase(worldPtr->entities.begin() + i);
		}
	}
	for (uint32_t i = worldPtr->cameras.size() - 1; i > -1; i--)
	{
		Entity* ent = worldPtr->cameras[i];
		if (ent->doNotDelete)
		{
			ent->lastWakeState = false;
			ent->Reset();
		}
		else
		{
			delete ent;
			worldPtr->cameras.erase(worldPtr->cameras.begin() + i);
		}
	}
	worldPtr->RebuildLayers();/**/
	std::cout << "reset\n";
	needsReset = false;
}

void Engine::Init()
{
	needsInit = false;
}

bool Engine::GameRunning() { return gameRunning; }
bool Engine::NeedsInit() { return needsInit; }

Engine::~Engine()
{
	for (uint32_t i = 0; i < worldPtr->entities.size(); i++)
	{
		delete worldPtr->entities[i];
	}
	for (uint32_t i = 0; i < worldPtr->cameras.size(); i++)
	{
		delete worldPtr->cameras[i];
	}
	for (uint32_t i = 0; i < worldPtr->prototypes.size(); i++)
	{
		delete worldPtr->prototypes[i];
	}
}
Engine::Engine(World* worldPtr, AssetManager* assetManagerPtr, Renderer* renderPtr)
{
	std::cout << MercutioVersion << "\n";
	this->worldPtr = worldPtr;
	this->assetManagerPtr = assetManagerPtr;
	this->renderPtr = renderPtr;
	random = &worldPtr->random;
}

void Engine::UpdateHelper(Entity* ent)
{
	//if (ent->random == nullptr) { ent->random = &random; }
	if (ent->awake == false)
	{
		ent->lastWakeState = false;
		return;
	}
	else if (ent->lastWakeState == false)
	{
		ent->Awake();
		ent->deltaTimeCo = &deltaTimeCo;
		ent->deltaTimeCoClock = &deltaTimeCoClock;
		ent->needsReset = &needsReset;
		ent->isPaused = &isPaused;
		ent->gameRunning = &gameRunning;
		ent->entities = &worldPtr->entities;
	}
	ent->lastWakeState = ent->awake;
	ent->windowWidth = (float)assetManagerPtr->windowWidth;
	ent->windowHeight = (float)assetManagerPtr->windowHeight;
	ent->deltaTime = deltaTime*deltaTimeCo*timeCo;
	
	ent->rawDeltaTime = deltaTime;
	ent->SysUpdate();
	ent->Update();

	//spawning
	for (unsigned int f = 0; f < ent->initQueue.size(); f++)
	{
		worldPtr->AddEntity(ent->initQueue.back());
		//worldPtr->entities.back()->doNotDelete = false;
		ent->initQueue.pop_back();
	}
}

void Engine::EntityUpdate()
{
	//use a while loop to ensure all objects are instantiated. could lead to infinite loop
	uint32_t i = 0;
	while (i < worldPtr->entities.size())
	{
		Entity* ent = worldPtr->entities[i];
		UpdateHelper(worldPtr->entities[i]);
		//if (needsReset) { return; }
		i++;
	}
	//cameras go last to accurately follow their subjects
	for (uint32_t i = 0; i < worldPtr->cameras.size(); i++)
	{
		UpdateHelper(worldPtr->cameras[i]);
	}
}

void Engine::FixedUpdate()
{
	int numEntities = worldPtr->entities.size();
	for (unsigned int i = 0; i < worldPtr->entities.size(); i++)
	{
		worldPtr->entities[i]->physObject.PhysUpdate();
		worldPtr->entities[i]->FixedUpdate();
	}
}

void Engine::PhysicsUpdate()
{
	unsigned int numEntities = worldPtr->entities.size();
	for each (Entity* ent in worldPtr->entities)
	{
		ent->boundingBox.transform.position = ent->transform.position;
		//std::cout << ent->boundingBox.transform.position.x << "\n";
		if (ent->awake == false) { continue; }
		if (ent->isTrigger) { continue; }
		if (ent->collides == false) { continue; }
		for each (Entity* var in worldPtr->entities)
		{
			if (var->awake == false) { continue; }
			if (ent == var) { continue; }
			if (var->collides == false) { continue; }
			if (ent->boundingBox.isColliding(var->boundingBox))
			{
				ent->OnCollision(var);
				if (var->isTrigger) { var->OnCollision(ent); }
			}
		}
	}/**/
}

void Engine::Update()
{
	if (needsInit) { Init(); }
	if (needsReset) { Reset(); }
	time = glfwGetTime();
	deltaTime = time - lastTime;
	lastTime = time;
	//std::cout << random.random() << "\n";
	if (!isPaused)
	{
		if (fixedTimer > fixedTime)
		{
			FixedUpdate();
			fixedTimer -= fixedTime;
		}
		fixedTimer += deltaTime;
		timeCo = 1;
		
	}
	else
	{
		timeCo = 0;
	}
	inputManager->Update(deltaTime, assetManagerPtr->window);
	//entity update
	EntityUpdate();
	//if (needsReset) { return; }
	//physics updater
	PhysicsUpdate();
	//render update
	renderPtr->Update(worldPtr->cameras[0]);
	//glfwSwapBuffers(assetManagerPtr->window);

	if (deltaTimeCoClock > 0) { deltaTimeCoClock -= deltaTime; }
	else { deltaTimeCoClock = 0; deltaTimeCo = 1; }

	/*if (glfwGetKey(assetManagerPtr->window, GLFW_KEY_TAB) == GLFW_PRESS && !resizedLastFrame)
	{
		if (toggle)
		{
			assetManagerPtr->windowWidth = 800;
			assetManagerPtr->windowHeight = 600;
			assetManagerPtr->viewWidth = 800;
			assetManagerPtr->viewHeight = 600;
			assetManagerPtr->SetSize();
		}
		else
		{
			assetManagerPtr->windowWidth = 1280;
			assetManagerPtr->windowHeight = 720;
			assetManagerPtr->viewWidth = 1280;
			assetManagerPtr->viewHeight = 720;
			assetManagerPtr->SetSize();
		}
		resizedLastFrame = true;
		toggle = !toggle;
	}
	else if (glfwGetKey(assetManagerPtr->window, GLFW_KEY_TAB) != GLFW_PRESS) { resizedLastFrame = false; }
	if (glfwGetKey(assetManagerPtr->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		//gameRunning = false;
		
	}/**/

	if (gameRunning == false)
	{
		glfwSetWindowShouldClose(assetManagerPtr->window, true);
	}
}