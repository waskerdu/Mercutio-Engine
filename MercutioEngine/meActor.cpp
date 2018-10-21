#include "stdafx.h"
#include "meActor.h"
#include <math.h>
#include "mePhysics.h"
#include "meEase.h"

void Actor::ManageProjectiles()
{
	float angle;
	//float moveAngle;
	float tempAngle;
	float angleDelta;
	float cosine;
	float sine;
	float offset;
	glm::vec3 tempPos;
	glm::vec2 aim;
	glm::vec3 tempV;
	bool fire = false;
	//init variables
	//offset = itemOffset * charge / maxCharge;
	offset = itemOffset * Quad::easeOut(charge / maxCharge);
	aim = controller->GetAxis2("aim");
	if (canFire == false) { aim *= 0; }
	tempPos = glm::vec3(chargeVec, 0) * offset;
	tempPos.z = GetChild(numBelts)->localTransform.position.z;
	angle = glm::atan(tempPos.y, tempPos.x);

	//manages charging
	if (glm::length(aim) > chargeDeadzone)
	{
		if (isDodging == false)
		{
			charge += chargeRate*(float)deltaTime;
		}
		chargeVec = glm::vec2(aim.x, aim.y);
	}
	else if (charge > launchCharge) { fire = true; }
	else
	{
		if (charge > 0) { charge -= chargeDrain*(float)deltaTime; }
		else { charge = 0; }
	}
	if (charge > maxCharge) { charge = maxCharge; }
	if (charge == maxCharge) { numCurrentProjectiles = numProjectiles + numBonusProjectiles; }
	else { numCurrentProjectiles = numProjectiles; }
	if (numCurrentProjectiles > maxProjectiles) { numCurrentProjectiles = maxProjectiles; std::cout << "too many projectiles!\n"; }
	if (charge > minCharge)
	{
		for (int i = 0; i < numCurrentProjectiles; i++)
		{
			GetChild(numBelts + i)->SetAwake(true);
		}
	}
	else
	{
		for (int i = 0; i < maxProjectiles; i++)
		{
			GetChild(numBelts + i)->SetAwake(false);
		}
	}

	//places projectiles
	if (projectilesParallel)
	{
		cosine = cos(angle + glm::radians(90.0f));
		sine = sin(angle + glm::radians(90.0f));
		tempPos.x -= cosine * chopstickSpacing * (numCurrentProjectiles - 1) * 0.5f;
		tempPos.y -= sine * chopstickSpacing * (numCurrentProjectiles - 1) * 0.5f;
		for (int i = 0; i < numCurrentProjectiles; i++)
		{
			GetChild(numBelts + i)->localTransform.position = tempPos;
			GetChild(numBelts + i)->transform.Rotate(glm::vec3(0, 0, angle));
			GetChild(numBelts + i)->physObject.velocity = glm::vec3(-chargeVec, 0);
			GetChild(numBelts + i)->SetAwake(charge > minCharge);
			tempPos.x += cosine * chopstickSpacing;
			tempPos.y += sine * chopstickSpacing;
		}
	}
	else
	{
		if (numCurrentProjectiles == 1)
		{
			tempAngle = angle;
			angleDelta = 0;
		}
		else
		{
			tempAngle = angle - glm::radians(spread * 0.5f);
			angleDelta = glm::radians(spread) / (numCurrentProjectiles - 1);
		}
		for (int i = 0; i < numCurrentProjectiles; i++)
		{
			tempPos.x = cos(tempAngle)*offset;
			tempPos.y = sin(tempAngle)*offset;
			tempV.x = -cos(tempAngle);
			tempV.y = -sin(tempAngle);
			GetChild(numBelts + i)->physObject.velocity = tempV;
			GetChild(numBelts + i)->localTransform.position = tempPos;
			GetChild(numBelts + i)->transform.Rotate(glm::vec3(0, 0, tempAngle));
			GetChild(numBelts + i)->SetAwake(charge > minCharge);
			tempAngle += angleDelta;
		}
	}

	//fire control
	if (fire)
	{
		float fireSpeed = projectileSpeed;
		if (instantCharge == false) { fireSpeed = fireSpeed * charge; }
		for (int i = 0; i < numCurrentProjectiles; i++)
		{
			Entity* newProjectilePtr;
			newProjectilePtr = GetChild(numBelts + i)->Copy();
			newProjectilePtr->parent = nullptr;
			newProjectilePtr->SetAwake(true);
			newProjectilePtr->kinematic = true;
			newProjectilePtr->SetDeleteStatus(false);
			newProjectilePtr->collides = true;
			newProjectilePtr->transform.RotateRelative(glm::vec3(0, 0, glm::radians(180.0f)));
			newProjectilePtr->physObject.velocity *= fireSpeed;
			initQueue.push_back(newProjectilePtr);
		}
		charge = 0;
		/*if (shootSound.getBuffer() != NULL)
		{
			shootSound.play();
		}/**/
		soundHolder->Play(attackSound);
	}
}

void Actor::ManageDash()
{
	Hit hit;
	glm::vec3 movement = glm::vec3(controller->GetAxis2("movement"), 0);
	float moveAngle  = glm::atan(movement.y, movement.x);
	float offset;
	switch (dash)
	{
	case Actor::Dashes::normal:
		if (controller->GetButton("dodge") && isDodging == false && glm::length(movement) > 0)
		{
			isDodging = true;
			moveLockClock = moveLockTime;
			invulnClock = dodgeTime;
			materialPtr = ninjaMatter;
		}
		if (isDodging && invulnClock > dodgeTime - moveLockTime && glm::length(physObject.velocity) > 0)
		{
			physObject.velocity = glm::normalize(physObject.velocity)*dodgeSpeed;
		}
		break;
	case Actor::Dashes::speed:
		isDodging = controller->GetButton("dodge_down");
		if (isDodging)
		{
			physObject.velocity = movement * speed * 2.5f;
		}
		break;
	case Actor::Dashes::damage:
		offset = dashClock / dashMax;
		
		offset = Quad::easeOut(offset);
		if (controller->GetButton("dodge_down") && isDodging == false)
		{
			dashClock += (float)deltaTime;
			if (dashClock > dashMax) { dashClock = dashMax; }
			GetChild((int)children.size() - 1)->transform.Rotate(glm::vec3(0, 0, moveAngle));
			GetChild((int)children.size() - 1)->localTransform.position = movement * damageDashOffset * offset;
			
			if (dashClock > dashThreshold)
			{
				GetChild((int)children.size() - 1)->SetAwake(true);
			}
			canMove = false;
		}
		else if (dashClock > dashThreshold && glm::length(movement) > 0.0f)
		{
			dashClock = 0.0f;
			isDodging = true;
			invulnClock = dodgeTime * offset;
			moveLockClock = moveLockTime * offset;
			physObject.velocity = glm::normalize(movement)*dodgeSpeed;
			canMove = true;
		}/**/
		else if (invulnClock == 0.0f)
		{
			canMove = true;
			dashClock = 0.0f;
			GetChild((int)children.size() - 1)->SetAwake(false);
		}
		/*if (controller->GetButton("dodge") && isDodging == false && glm::length(movement) > 0)
		{
			isDodging = true;
			invulnClock = dodgeTime;
			moveLockClock = moveLockTime;
		}
		if (isDodging && glm::length(physObject.velocity) > 0)
		{
			physObject.velocity = glm::normalize(physObject.velocity)*dodgeSpeed;

			moveAngle = glm::atan(physObject.velocity.y, physObject.velocity.x);
			GetChild((int)children.size() - 1)->SetAwake(true);
			GetChild((int)children.size() - 1)->transform.Rotate(glm::vec3(0, 0, moveAngle));
		}
		else
		{
			physObject.velocity = movement*speed;
			GetChild((int)children.size() - 1)->SetAwake(false);
		}/**/
		break;
	case Actor::Dashes::teleport:
		if (controller->GetButton("dodge"))
		{
			Physics::Raycast(this, &hit, transform.position, transform.position + movement*teleportDistance);
			transform.position = hit.position;
		}
		break;
	default:
		break;
	}
}

void Actor::SetWeapon(Weapons::Weapon newWeapon)
{

}

void Actor::SetWeapon(Entity* newWeapon)
{
	Projectile* newPro;
	Projectile* oldPro;
	newPro = dynamic_cast<Projectile*>(newWeapon);
	chargeRate = newPro->chargeRate * chargeRateMult;
	projectileSpeed = newPro->speed * projectileSpeedMult;
	for (int i = 0; i < maxProjectiles; i++)
	{
		oldPro = dynamic_cast<Projectile*>(GetChild(numBelts + i));
		oldPro->health = newPro->health;
		oldPro->meshPtr = newPro->meshPtr;
		oldPro->materialPtr = newPro->materialPtr;
		oldPro->boundingBox.transform = newPro->boundingBox.transform;
		oldPro->physObject.drag = newPro->physObject.drag;
		oldPro->physObject.bounceType = newPro->physObject.bounceType;
		oldPro->alias = newPro->alias;
		//oldPro->explodes = true;
	}
}

void Actor::SetDash(Dashes::Dash newDash)
{

}

void Actor::SetCharacter(Character character)
{
	this->character = character;
	alive = true;
	canFire = true;
	canMove = true;
	instantCharge = false;
	transform.Rotate(glm::vec3(0, 0, 0));
	//Entity* newProjectilePtr;
	//Entity* newWave;
	projectilesParallel = true;
	numProjectiles = 1;
	numBonusProjectiles = 0;
	invulnClock = 0;
	isDodging = false;
	moveLockClock = 0;
	charge = 0;

	if (RandInt(0, 1) == 0)
	{
		attackSound = "tan_attack";
		damageSound = "tan_damage";
		deathSound = "tan_death";
		selectSound = "tan_select";
	}
	else
	{
		attackSound = "red_attack";
		damageSound = "red_damage";
		deathSound = "red_death";
		selectSound = "red_select";
	}

	/*if (character != Actor::none && character != Actor::Character::none)
	{
		soundHolder->Play(selectSound);
	}/**/
	//

	

	switch (character)
	{
	case Actor::red:
		materialPtr = redMatter;
		lastMatter = redMatter;
		//speed = 400;
		projectileSpeed = 800;
		maxHealth = 3;
		invulnTime = 3;
		SetWeapon(wok);
		dash = Dashes::normal;
		break;
	case Actor::ted:
		materialPtr = tedMatter;
		lastMatter = tedMatter;
		//speed = 400;
		projectileSpeed = 600;
		maxHealth = 5;
		invulnTime = 4;
		SetWeapon(roller);
		dash = Dashes::damage;
		break;
	case Actor::tan:
		materialPtr = tanMatter;
		lastMatter = tanMatter;
		//speed = 400;
		maxHealth = 3;
		invulnTime = 3;
		SetWeapon(chopstick);
		numProjectiles = 2;
		dash = Dashes::teleport;
		break;
	case Actor::key:
		materialPtr = keyMatter;
		lastMatter = keyMatter;
		//speed = 400;
		projectileSpeed = 800;
		maxHealth = 3;
		invulnTime = 3;
		//numProjectiles = 5;
		numBonusProjectiles = 4;
		projectilesParallel = false;
		SetWeapon(spoon);
		dash = Dashes::speed;
		instantCharge = true;
		break;
	case Actor::none:
		SetCharacter(red);
		materialPtr = ninjaMatter;
		lastMatter = ninjaMatter;
		this->character = Actor::none;
		dash = Dashes::none;
		canFire = false;
	default:
		break;
	}
	health = maxHealth;
	for (size_t i = 0; i < children.size(); i++)
	{
		/*if ((int)i < numBelts + numProjectiles)
		{
			children[i]->SetAwake(true);
		}
		else
		{
			children[i]->SetAwake(false);
		}*/
		children[i]->SetAwake(false);
	}
	//SetBelts(false);
	SetHearts();
}

bool Actor::ShieldDeflected(Entity* ent)
{
	//
	float shunt = 5.0f;
	if (GetChild(5)->alias == "wok")
	{
		if (charge == maxCharge)
		{
			float dot = glm::dot(glm::normalize(glm::vec3(chargeVec, 0)), glm::normalize(transform.position - ent->transform.position));
			if (dot < -0.6f)
			{
				ent->physObject.velocity.x = -ent->physObject.velocity.x;
				ent->physObject.velocity.y = -ent->physObject.velocity.y;
				ent->SendMessage("active");
				return true;
			}
		}
	}
	return false;
}

void Actor::OnCollision(Entity* ent)
{
	if (ent->tags.count("projectile") == 1)
	{
		if (ent->tags.count("hero") == 0) 
		{ 
			if (ent->tags.count("bomb") == 1) 
			{ 
				if (ShieldDeflected(ent)) { return; }
				if (invulnClock == 0)
				{
					health-=2;
					//SetBelts();
					SetHearts();
					invulnClock = invulnTime;
				}
			}
			else
			{
				if (ShieldDeflected(ent)) { return; }
				Damage();
			}
		}
	}
	if (ent->tags.count("bad") == 1 && dash == Dashes::damage && isDodging)
	{
		ent->Damage();
	}
}

void Actor::SetHearts()
{
	float yoffset = 70.0f;
	float xoffset = - maxHealth * heartSpacing / 2.0f;
	for (size_t i = 0; i < 5; i++)
	{
		//GetChild(i)->localTransform.position.y = 50.0f;
		//GetChild(i)->localTransform.position.x = -50.0f + i * 20.0f;
		GetChild(i)->localTransform.position = glm::vec3(xoffset + heartSpacing * i, yoffset, 0.0f);
		if ((int)i < health)
		{
			GetChild(i)->materialPtr = heartMatter;
		}
		else
		{
			GetChild(i)->materialPtr = heartDeadMatter;
		}
		if ((int)i < maxHealth)
		{
			GetChild(i)->SetAwake(true);
		}
		else
		{
			GetChild(i)->SetAwake(false);
		}
	}
}

void Actor::SetBelts(bool spawn)
{
	for (int i = 0; i < numBelts; i++)
	{
		if (health - 1 < i)
		{
			if (spawn)
			{
				initQueue.push_back(GetChild(i)->Copy());
				initQueue.back()->SetParent(nullptr);
				initQueue.back()->SetDeleteStatus(false);
			}
			GetChild(i)->SetAwake(false);
		}
		else{ GetChild(i)->SetAwake(true); }
	}
}

void Actor::Damage()
{
	if (invulnClock == 0)
	{
		health--;
		if (health < 0)
		{
			soundHolder->Play(deathSound);
		}
		else
		{
			soundHolder->Play(damageSound);
		}
		
		//SetBelts();
		SetHearts();
		invulnClock = invulnTime;
	}
}

Actor::Actor()
{
	initQueue = std::vector<Entity*>();
	boundingBox.transform.scale = transform.scale * 50.0f;
	boundingBox.transform.position = transform.position;
	health = maxHealth;
}

Entity* Actor::Copy()
{
	//copy creates a new object based on another object and returns it. sub classes will write their own version
	Actor* copy = new Actor(*this);
	DeepCopy(this, copy);
	return copy;
}

void Actor::Update()
{
	Hit hit;
	animTimer++;
	if (animTimer % 6 == 0)
	{
		currentFrame++;
	}
	if (currentFrame == 4.0f) { currentFrame = 0.0f; }
	for (size_t i = 0; i < 5; i++)
	{
		if ((int)i < maxHealth && controller->GetButton("healthDisplay"))
		{
			GetChild(i)->SetAwake(true);
		}
		else if (invulnClock == 0.0f)
		{
			GetChild(i)->SetAwake(false);
		}
	}

	if (health < 0)
	{
		health = -1;
		if (alive)
		{
			//spawn body
			Entity* corpse = GetChild(0)->Copy();//should be a belt
			corpse->materialPtr = materialPtr;
			corpse->transform.Rotate(glm::vec3(0, 0, glm::radians(90.0f)));
			corpse->parent = nullptr;
			corpse->SetAwake(true);
			corpse->DeleteOnReset(true);
			initQueue.push_back(corpse);
			alive = false;
		}
	}
	if (alive == false && initQueue.size() == 0)
	{
		SetAwake(false);
		return;
	}
	if (moveLockClock > 0.0f)
	{
		canChangeCourse = false;
		moveLockClock -= (float)deltaTime;
	}
	else
	{
		canChangeCourse = true;
	}
	if (invulnClock > 0)
	{
		invulnClock -= (float)deltaTime;
		isVisible = true;
		if ((int)(invulnClock * 20) % 3 == 0 && isDodging == false)
		{
			isVisible = false;
		}
	}
	else 
	{ 
		invulnClock = 0; 
		isVisible = true;
		isDodging = false;
		if (lastMatter != nullptr)
		{
			materialPtr = lastMatter;
		}
	}
	if (controller != nullptr)
	{
		bool fire = false;
		if (controller->GetButton("suicide")) 
		{ 
			health = -1; 
		}
		
		float angle;
		float offset;
		glm::vec3 tempPos;
		glm::vec2 aim;
		glm::vec3 tempV;
		offset = itemOffset * charge / maxCharge;
		aim = controller->GetAxis2("aim");
		if (canFire == false) { aim *= 0; }
		tempPos = glm::vec3(aim, 0) * offset;
		tempPos.z = GetChild(numBelts)->localTransform.position.z;
		
		angle = glm::atan(tempPos.y, tempPos.x);
		glm::vec3 movement = glm::vec3(controller->GetAxis2("movement"), 0);
		
		if (!canMove) { movement *= 0; }
		if(canChangeCourse)
		{ 
			//physObject.velocity = movement*speed; 
			if (glm::length(movement) > 0.0f)
			{
				physObject.velocity = speed * glm::normalize(movement) * Quad::easeIn(glm::length(movement));
			}
			else
			{
				physObject.velocity *= 0.0f;
			}
		}
		ManageDash();
		ManageProjectiles();
	}
}