#include "stdafx.h"
#include "wokDoor.h"


Door::Door()
{
}


Door::~Door()
{
}

void Door::Update()
{
	//std::cout << transform.position.y << " " << targetPos.y << "\n";
	if (transform.position != targetPos)
	{
		//std::cout << "seek\n";
		float currentSpeed = (float)(speed/deltaTime);
		currentSpeed = speed;
		glm::vec3 diff = targetPos - transform.position;
		//std::cout << glm::length(diff) << "\n";
		if (glm::length(diff) < closeEnough)
		{
			transform.position = targetPos;
			physObject.velocity *= 0;
		}
		else
		{
			physObject.velocity = glm::normalize(diff)*currentSpeed;
		}
	}
}

void Door::SendMessage(std::string message)
{
	if (message == "open") { Open(); /*std::cout << openPos.x << " " << openPos.y << "\n";*/ }
	if (message == "close") { Close(); }
}

void Door::OnCollision(Entity* ent)
{
	//figure out whether x or y interpenetration depth is greater
	//place colliding entity at x or y intersection and cancel its velocity along that axis
	//does not collide with other doors or barriers so should have a tag
	if (ent->tags.count("barrier") || ent->tags.count("door")) { return; }
	if (transform.position.x != targetPos.x || transform.position.y != targetPos.y) { return; } //disable collision while door is moving
	bool xLimited;
	float distance;
	boundingBox.CollisionDepth(ent->boundingBox, &xLimited, &distance);
	if (xLimited)
	{
		ent->transform.position.x = transform.position.x - distance * 1.001f;
		if (ent->physObject.bounceType == PhysObject::halt)
		{
			ent->physObject.velocity *= 0;
		}
		else if (ent->physObject.bounceType == PhysObject::bounce)
		{
			ent->physObject.velocity.x *= -1;
		}
		else //slide
		{
			ent->physObject.velocity.x = 0;
		}
	}
	else
	{
		ent->transform.position.y = transform.position.y - distance*1.001f;
		if (ent->physObject.bounceType == PhysObject::halt)
		{
			ent->physObject.velocity *= 0;
		}
		else if (ent->physObject.bounceType == PhysObject::bounce)
		{
			ent->physObject.velocity.y *= -1;
		}
		else //slide
		{
			ent->physObject.velocity.y = 0;
		}
	}/**/
	//std::cout << xLimited << "\n";
	//float 
	//float xPenDepth=boundingBox.transform.scale.x+boundingBox.transform.position.x-(ent->boundingBox.transform.scale.x+
}


Entity* Door::Copy()
{
	//copy creates a new object based on another object and returns it. sub classes will write their own version
	Door* copy = new Door(*this);
	DeepCopy(this, copy);
	return copy;
}