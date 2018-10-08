#pragma once
#include <vector>
#include <set>
#include "meMath.h"
#include "meMesh.h"
#include "mePhysObject.h"
#include <SFML\Audio.hpp>
#include "meTransform.h"
#include "meInputController.h"
#include "meMaterial.h"
#include "meRandom.h"
#include "assets\shaders\preamble.glsl"
#include "meMessage.h"
#include "meRenderData.h"
#include "meMonitorMode.h"

class Entity
{
	bool lastWakeState = false;
	bool privateWakeState = true;
	bool awake = true;
	Random* random;
	double* deltaTimeCo;
	bool* needsReset;
	bool* isPaused;
	bool* gameRunning;
	std::vector<Entity*>* entities;
	friend struct EngineInterface;
	friend class Physics;
	friend class World;
	friend class Renderer;
	std::vector<glm::vec3> debugVerts;
	MonitorMode** tempMonitorMode;
	MonitorMode::WindowMode* windowMode;
	bool* optionsConfirm;
	bool* modeChanged;
	int* vsync;
public:
	enum Layer
	{
		terrain,
		static_projectile,
		dead_enemy,
		item,
		enemy,
		live_projectiles,
		player,
		belt,
		ui
	};
	Transform transform;
	Transform localTransform;
	Mesh* meshPtr;
	Material* materialPtr;
	std::vector<Entity*> children;
	Entity* parent;
	std::vector<Entity*> initQueue;
	PhysObject physObject;
	std::string alias;
	//Random* random;
	double* deltaTimeCoClock; //should be moved up to private and getter and setter methods added
	double localDeltaTimeCo = 1;

	BoundingRect boundingBox;
	bool isTrigger = false;
	bool collides = false;
	bool isVisible = true;
	double deltaTime = 0;
	double rawDeltaTime = 0;
	float windowHeight = 0;
	float windowWidth = 0;
	std::set<std::string> tags;
	bool doNotDelete = true;
	bool kinematic = true;
	Layer layer = terrain;
	float currentFrame = 0.0f;
	float numFrames = 1.0f;
	float flip = 1.0f;
private:
	
	friend class Engine;
	friend class World;
	void SysUpdate();
	void SysFixedUpdate();
	void SetAwakeRemote(bool awakeState);
	void DebugRender(glm::mat4* matrix);
protected:
	void DeepCopy(Entity* source, Entity* copy);
	virtual void Awake() {}
	virtual void Update() {}
	virtual void FixedUpdate() {}
	virtual void OnCollision(Entity* collider) {}
	virtual void ProcessMessage(Message message){}
public:
	
	Entity();
	virtual Entity* Copy();
	//virtual void Render(glm::mat4* viewMatrix, glm::mat4* worldMatrix);
	virtual void Render(RenderData* data);
	virtual void Bind();
	void RemoveChild(int ind);
	void AddChild(Entity* child);
	void SetParent(Entity* parent);
	Entity* GetChild(int ind);
	void SetAwake(bool awakeState);
	bool isAwake() { return awake; }
	double RandReal();
	int RandInt(int min, int max);
	void RandSetSeed(uint32_t seed);
	double GetDeltaTimeCo() 
	{ 
		if (deltaTimeCo == nullptr) { return 1; }
		return *deltaTimeCo; 
	}
	void SetDeltaTimeCo(double deltaTimeCo) { *(this->deltaTimeCo) = deltaTimeCo; }
	void SetDeleteStatus(bool status);//depriciated. use DeleteOnReset instead
	void DeleteOnReset(bool del)
	{
		doNotDelete = !del;
		for (uint32_t i = 0; i < children.size(); i++)
		{
			children[i]->DeleteOnReset(del);
		}
	}

	void DebugCircle(float radius, int sides = 32);
	void DebugLine(glm::vec3 p0, glm::vec3 p1);
	void DebugClear() { debugVerts.clear(); }
	virtual ~Entity();
	virtual void Damage() {}
	virtual void Reset(){}
	virtual void SendMessage(std::string name){}
	virtual void SendMessage(std::string name, float val){}
	virtual void SendMessage(std::string name, Entity* ent) {}
};