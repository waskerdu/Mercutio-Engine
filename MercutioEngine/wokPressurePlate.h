#pragma once
#include "meEntity.h"
class PressurePlate :
	public Entity
{
	bool isDown = false;
	bool isDownLast = false;
	std::string message = "none";
	std::string activatorTag = "hero";
	std::vector<Entity*> targets;
public:
	Material* upMatter;
	Material* downMatter;
	std::vector<std::string> targetAliases;
private:
public:
	PressurePlate();
	~PressurePlate();
	void SetMessage(std::string message) { this->message = message; }
	void AddTarget(Entity* target) { targets.push_back(target); }
	void RemoveTarget(Entity* target);
	void ClearTargets() { targets.clear(); }
	void OnCollision(Entity* ent);
	void Update();
	Entity* Copy();
};

