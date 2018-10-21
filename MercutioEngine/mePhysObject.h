#pragma once
#include "meMath.h"
#include "meTransform.h"

struct PhysObject
{
	glm::vec3 velocity;
	glm::vec3 acceleration;
	enum BounceType
	{
		halt,
		slide,
		bounce
	};
	BounceType bounceType = halt;
	double bounceE = 0;//efficiency of bounce
	float drag = 0;
	void PhysUpdate()
	{
		velocity += acceleration;
		if (glm::length(velocity) > drag)
		{
			velocity = (glm::length(velocity) - drag) * glm::normalize(velocity);
		}
		else
		{
			velocity *= 0;
		}
	}
};

struct BoundingRect
{
	Transform transform;
	glm::vec3 debugColor;
	bool isLineColliding(glm::vec3 pos0, glm::vec3 pos1)
	{
		return false;
	}
	bool isColliding(BoundingRect &other)
	{
		return (abs(transform.position.x - other.transform.position.x) < transform.scale.x + other.transform.scale.x) &&
			(abs(transform.position.y - other.transform.position.y) < transform.scale.y + other.transform.scale.y);
	}
	void CollisionDepth(BoundingRect &other, bool* xLimited, float* distance)
	{
		float xDistance = (transform.scale.x + other.transform.scale.x) - abs(transform.position.x - other.transform.position.x);
		float yDistance = (transform.scale.y + other.transform.scale.y) - abs(transform.position.y - other.transform.position.y);
		if (xDistance < yDistance)
		{
			*xLimited = true;
			*distance = transform.position.x - other.transform.position.x;
			if (*distance < 0) { *distance -= xDistance; }
			else { *distance += xDistance; }
		}
		else
		{
			*xLimited = false;
			*distance = transform.position.y - other.transform.position.y;
			if (*distance < 0) { *distance -= yDistance; }
			else { *distance += yDistance; }
		}/**/
	}
};