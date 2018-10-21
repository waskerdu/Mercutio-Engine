#pragma once
#include "meEntity.h"
#include "meActor.h"
#include "meSoundHolder.h"
class CharacterSelector :
	public Entity
{
	Actor::Character character = Actor::red;
public:
	std::vector<Material*> materials;
	void SetCharacter(Actor::Character character);
	CharacterSelector();
	~CharacterSelector();
	void OnCollision(Entity* ent);
	void Awake();
	Entity* Copy();
	SoundHolder* soundHolder;
};

