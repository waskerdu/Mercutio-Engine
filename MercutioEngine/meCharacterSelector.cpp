#include "stdafx.h"
#include "meCharacterSelector.h"

CharacterSelector::CharacterSelector()
{
}


CharacterSelector::~CharacterSelector()
{
}

void CharacterSelector::Awake()
{
	isTrigger = true;
}

void CharacterSelector::OnCollision(Entity* ent)
{
	if (ent->tags.count("hero") == 1 && character != Actor::none)
	{
		Actor* actor = dynamic_cast<Actor*>(ent);
		if (actor->character != character)
		{
			actor->SetCharacter(character);
		}
	}
}

void CharacterSelector::SetCharacter(Actor::Character character)
{
	this->character = character;
	materialPtr = materials.at((int)character);
}

Entity* CharacterSelector::Copy()
{
	//copy creates a new object based on another object and returns it. sub classes will write their own version
	CharacterSelector* copy = new CharacterSelector(*this);
	DeepCopy(this, copy);
	return copy;
}