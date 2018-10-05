#include "stdafx.h"
#include "meEnemy.h"
#include "mePhysics.h"

Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

void Enemy::SetType(EnemyType newType)
{
	transform.scale = glm::vec3(1);
	switch (newType)
	{
	case Enemy::charger:
		materialPtr = chargerMatter;
		break;
	case Enemy::thrower:
		materialPtr = throwerMatter;
		break;
	case Enemy::bomber:
		materialPtr = bomberMatter;
		break;
	case Enemy::suicide:
		break;
	case Enemy::gobble:
		break;
	case Enemy::gobble_thrower:
		break;
	default:
		break;
	}
}

void Enemy::Awake()
{
	for (uint32_t i = 1; i < children.size(); i++)
	{
		children[i]->SetAwake(false);
	}
}

void Enemy::SetVelocity(glm::vec3 target, float speed)
{
	physObject.velocity = target-transform.position;
	physObject.velocity.z = 0;
	physObject.velocity = glm::normalize(physObject.velocity)*speed;
}

void Enemy::OnCollision(Entity* collision)
{
	if (collision->tags.count("projectile") == 1 && collision->tags.count("hero") == 1)
	{
		Damage();
	}
	else if (collision->tags.count("bad") != 0)
	{
		glm::vec3 repelVec = transform.position - collision->transform.position;
		if (glm::length(repelVec) == 0.0f) { repelVec.x = (float)RandReal() - 0.5f; repelVec.y = (float)RandReal() - 0.5f;}
		physObject.velocity += glm::normalize(repelVec)*avoid;
		physObject.velocity.z = 0;
		if (glm::length(physObject.velocity) > speed)
		{
			physObject.velocity = glm::normalize(physObject.velocity)*speed;
		}
	}
	else if (collision->tags.count("hero") != 0)
	{
		collision->Damage();
	}
}

void Enemy::Damage()
{
	if (alive)
	{
		alive = false;
		Entity* newBody;
		newBody = new Entity(*body->Copy());
		newBody->transform.position = transform.position;
		initQueue.push_back(newBody);
	}
}

Entity* Enemy::Copy()
{
	//copy creates a new object based on another object and returns it. sub classes will write their own version
	Enemy* copy = new Enemy(*this);
	DeepCopy(this, copy);
	return copy;
}

void Enemy::Update()
{
	if (target == nullptr) { state = Enemy::wandering; }
	if (!alive && initQueue.size() == 0) { SetAwake(false); return; }
	float distance;
	Hit hit;
	newState = false;
	if (state != oldState)
	{
		newState = true;
	}
	oldState = state;
	//std::cout << clock << "\n";
	int randomTarget;
	switch (state)
	{
	case Enemy::wandering:
		if (newState)
		{
			enemyAggro->SetAwake(true);
			enemyAggro->targets.clear();
			enemyAggro->targetsRef.clear();
		}
		//navigate to next node if nav path is on
		/*if (navSystem.navPath.size() > 0)
		{
			glm::vec3 destination = navSystem.GetNode(transform.position);
			physObject.velocity = glm::normalize(destination - transform.position)*speed;
		}*/
		//check if enemy aggro has a target
		if (enemyAggro->targets.size() > 0)
		{
			state = state = Enemy::persuing;
			randomTarget = RandInt(0, (int)enemyAggro->targets.size() - 1);
			target = enemyAggro->targets[randomTarget];
			enemyAggro->SetAwake(false);
		}
		/*if (enemyAggro->target != nullptr)
		{
			state = Enemy::persuing;
			target = enemyAggro->target;
		}/**/
		break;
	case Enemy::persuing:
		if (target->isAwake() == false)
		{
			state = Enemy::wandering;
			break;
		}
		distance = glm::length(target->transform.position - transform.position);
		if (type == charger)
		{
			if (distance < attackRange && distance > persueRange)
			{
				state = Enemy::charging;
			}
			else if (distance < chaseRange)
			{
				SetVelocity(target->transform.position, speed);
				/*physObject.velocity = target->transform.position - transform.position;
				physObject.velocity.z = 0;
				physObject.velocity = glm::normalize(physObject.velocity)*speed;*/
			}
			else
			{
				state = Enemy::wandering;
			}
		}
		else if (type == thrower || type == bomber)
		{
			if (distance < persueRange)
			{
				SetVelocity(target->transform.position, -speed);
			}
			else if (distance > attackRange)
			{
				SetVelocity(target->transform.position, speed);
			}
			else
			{
				state = Enemy::charging;
			}
		}
		break;
	case Enemy::charging:
		if (newState)
		{
			if (type == charger)
			{
				GetChild(1)->SetAwake(true);//charge notification. right now is a dumb exclamation point
			}
			else if (type == thrower)
			{
				GetChild(2)->SetAwake(true);
			}
			else if (type == bomber)
			{
				GetChild(3)->SetAwake(true);//should be bomb target
				//Physics::Raycast(this, &hit, transform.position + glm::normalize(target->transform.position - transform.position)*200.0f, target->transform.position);
				//std::cout << hit.position.x << " " << hit.position.y << "\n";
				GetChild(3)->localTransform.position = (target->transform.position - transform.position) * 0.5f;
				GetChild(4)->SetAwake(true);//should be pork bun
				GetChild(4)->localTransform.position = glm::normalize(transform.position - target->transform.position) * 100.0f;
			}
			physObject.velocity *= 0;
			clock = chargeTime;
		}
		physObject.velocity *= 0;
		if (clock == 0) 
		{ 
			state = Enemy::attacking; 
			if (type == charger)
			{
				GetChild(1)->SetAwake(false);
			}
			else if (type == thrower)
			{
				GetChild(2)->SetAwake(false);
			}
			else if (type == bomber)
			{
				GetChild(3)->SetAwake(false);
				GetChild(4)->SetAwake(false);
			}
		}
		//position projectile
		GetChild(2)->physObject.velocity = target->transform.position - transform.position;
		GetChild(2)->physObject.velocity.z = 0;
		GetChild(2)->physObject.velocity = glm::normalize(GetChild(2)->physObject.velocity)*projectileSpeed;
		GetChild(2)->transform.Rotate(glm::vec3(0, 0, glm::atan(GetChild(2)->physObject.velocity.y, GetChild(2)->physObject.velocity.x)));

		GetChild(4)->physObject.velocity = GetChild(3)->transform.position - transform.position;
		GetChild(4)->physObject.velocity.z = 0;
		GetChild(4)->physObject.velocity = glm::normalize(GetChild(4)->physObject.velocity)*projectileSpeed;
		GetChild(4)->transform.Rotate(glm::vec3(0, 0, glm::atan(GetChild(4)->physObject.velocity.y, GetChild(4)->physObject.velocity.x)));
		/*else
		{
			//position projectile
			GetChild(2)->physObject.velocity = target->transform.position-transform.position;
			GetChild(2)->physObject.velocity.z = 0;
			GetChild(2)->physObject.velocity = glm::normalize(GetChild(2)->physObject.velocity)*projectileSpeed;
			GetChild(2)->transform.Rotate(glm::vec3(0, 0, glm::atan(GetChild(2)->physObject.velocity.y, GetChild(2)->physObject.velocity.x)));

			GetChild(4)->physObject.velocity = GetChild(3)->transform.position - transform.position;
			GetChild(4)->physObject.velocity.z = 0;
			GetChild(4)->physObject.velocity = glm::normalize(GetChild(4)->physObject.velocity)*projectileSpeed;
			GetChild(4)->transform.Rotate(glm::vec3(0, 0, glm::atan(GetChild(4)->physObject.velocity.y, GetChild(4)->physObject.velocity.x)));
		}/**/
		break;
	case Enemy::attacking:
		if (newState)
		{
			if (type == charger)
			{
				SetVelocity(target->transform.position, attackSpeed);
				oldPosition = transform.position;
				clock = chaseTime;
			}
			else if (type == thrower)
			{
				initQueue.push_back(GetChild(2)->Copy());
				initQueue.back()->kinematic = true;
				initQueue.back()->collides = true;
				initQueue.back()->SetAwake(true);
			}
			else if (type == bomber)
			{
				initQueue.push_back(GetChild(4)->Copy());
				initQueue.back()->kinematic = true;
				initQueue.back()->collides = true;
				initQueue.back()->SetAwake(true);
			}
		}
		if (clock == 0)
		{
			state = Enemy::wandering;
		}
		//if (glm::length(transform.position - oldPosition) > attackDistance) { state = Enemy::wandering; }
		break;
	default:
		break;
	}
	if (clock > 0) { clock -= (float)deltaTime; }
	else { clock = 0; }
}
