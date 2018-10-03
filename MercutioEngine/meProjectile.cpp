#include "stdafx.h"
#include "meProjectile.h"


Projectile::Projectile()
{
}

Projectile::~Projectile()
{
}

void Projectile::OnCollision(Entity* collider)
{
	if (collider->tags.count(targetTag) == 1 || collider->tags.count("barrier") == 1)
	{
		health--;//gets fired twice per bad guy. kind of annoying fix later
		if (health == 0 && state == active)
		{
			/*physObject.velocity *= 0;
			collides = false;
			if (staticP != nullptr && alive)
			{
				initQueue.push_back(staticP->Copy());
				initQueue.back()->materialPtr = materialPtr;
				initQueue.back()->meshPtr = meshPtr;
				initQueue.back()->SetAwake(true);
				initQueue.back()->transform = transform;
				//staticP = nullptr;
			}
			if (alive) { alive = false; }/**/
			state = dead;
			if (explodes) { state = exploding; }
		}
	}
}

void Projectile::Update()
{
	if (!alive && !collides) { SetAwake(false); return; }
	bool newState = (state != lastState);
	switch (state)
	{
	case Projectile::active:
		if (glm::length(physObject.velocity) == 0) 
		{ 
			state = dead; 
			if (explodes) { state = exploding; }
		}
		break;
	case Projectile::dead:
		collides = false;
		physObject.velocity *= 0.0f;
		if (staticP != nullptr && alive && explodes == false)
		{
			initQueue.push_back(staticP->Copy());
			initQueue.back()->materialPtr = materialPtr;
			initQueue.back()->meshPtr = meshPtr;
			initQueue.back()->SetAwake(true);
			initQueue.back()->transform = transform;
		}
		if (alive) { alive = false; }
		break;
	case Projectile::exploding:
		if (newState) 
		{ 
			physObject.velocity *= 0.0f;
			explodeClock = explodeTime; 
			materialPtr = explodeMatter;
			transform.scale = explodeScale * glm::vec3(1);
			boundingBox.transform.scale = explodeScale * glm::vec3(1) * 50.0f;
		}
		if (explodeClock < 0.0f) { state = dead; }
		//std::cout << explodeClock << "\n";
		explodeClock -= (float)deltaTime;
		break;
	default:
		break;
	}
	lastState = state;
}

Entity* Projectile::Copy()
{
	Projectile* copy = new Projectile(dynamic_cast<const Projectile&>(*this));
	DeepCopy(this, copy);
	return copy;
}
