#include "stdafx.h"
#include "meBarrier.h"


Barrier::Barrier()
{
	tags.insert("barrier");
}


Barrier::~Barrier()
{
}

void Barrier::OnCollision(Entity* ent)
{
	//figure out whether x or y interpenetration depth is greater
	//place colliding entity at x or y intersection and cancel its velocity along that axis
	//does not collide with other barriers so should have a tag
	if (ent->tags.count("barrier") == 1 || ent->tags.count("door")) { return; }
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
		//if (ent->tags.count("bounce") == 1)
		{
			ent->physObject.velocity.x *= -1;
		}
		else
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
		//if (ent->tags.count("bounce") == 1)
		{
			ent->physObject.velocity.y *= -1;
		}
		else
		{
			ent->physObject.velocity.y = 0;
		}
	}
	//std::cout << xLimited << "\n";
	//float 
	//float xPenDepth=boundingBox.transform.scale.x+boundingBox.transform.position.x-(ent->boundingBox.transform.scale.x+
}
