#pragma once

#include "meMath.h"
#include "meTransform.h"
#include "mePhysObject.h"
#include <iostream>

struct Hit
{
	glm::vec3 position;
	Entity* entHit;
};

class Physics
{
	static bool inline GetIntersection(float fDst1, float fDst2, glm::vec3 P1, glm::vec3 P2, glm::vec3 &Hit, float &hitDis)
	{
		if ((fDst1 * fDst2) >= 0.0f) return false;
		if (fDst1 == fDst2) return false;
		glm::vec3 testHit= P1 + (P2 - P1) * (-fDst1 / (fDst2 - fDst1));
		//Hit = P1 + (P2 - P1) * (-fDst1 / (fDst2 - fDst1));
		if (glm::length(testHit - P1) < hitDis)
		{
			Hit = testHit;
			hitDis = glm::length(testHit - P1);
			return true;
		}
		return false;
	}

	static int inline InBox(glm::vec3 Hit, glm::vec3 B1, glm::vec3 B2, const int Axis)
	{
		if (Axis == 1 && Hit.z > B1.z && Hit.z < B2.z && Hit.y > B1.y && Hit.y < B2.y) return 1;
		if (Axis == 2 && Hit.z > B1.z && Hit.z < B2.z && Hit.x > B1.x && Hit.x < B2.x) return 1;
		if (Axis == 3 && Hit.x > B1.x && Hit.x < B2.x && Hit.y > B1.y && Hit.y < B2.y) return 1;
		return 0;
	}
	// returns true if line (L1, L2) intersects with the box (B1, B2)
	// returns intersection point in Hit
	static int CheckLineBox(glm::vec3 B1, glm::vec3 B2, glm::vec3 L1, glm::vec3 L2, glm::vec3 &Hit)
	{
		if (L2.x < B1.x && L1.x < B1.x) return false;
		if (L2.x > B2.x && L1.x > B2.x) return false;
		if (L2.y < B1.y && L1.y < B1.y) return false;
		if (L2.y > B2.y && L1.y > B2.y) return false;
		if (L2.z < B1.z && L1.z < B1.z) return false;
		if (L2.z > B2.z && L1.z > B2.z) return false;
		if (L1.x > B1.x && L1.x < B2.x &&
			L1.y > B1.y && L1.y < B2.y &&
			L1.z > B1.z && L1.z < B2.z)
		{
			Hit = L1;
			return true;
		}
		bool didHit = false;
		float hitDis = glm::length(L2 - L1);
		glm::vec3 tempHit = Hit;
		if (GetIntersection(L1.x - B1.x, L2.x - B1.x, L1, L2, tempHit, hitDis) && InBox(tempHit, B1, B2, 1)) { didHit = true; Hit = tempHit; }
		if (GetIntersection(L1.y - B1.y, L2.y - B1.y, L1, L2, tempHit, hitDis) && InBox(tempHit, B1, B2, 2)) { didHit = true; Hit = tempHit; }
		if (GetIntersection(L1.z - B1.z, L2.z - B1.z, L1, L2, tempHit, hitDis) && InBox(tempHit, B1, B2, 3)) { didHit = true; Hit = tempHit; }

		if (GetIntersection(L1.x - B2.x, L2.x - B2.x, L1, L2, tempHit, hitDis) && InBox(tempHit, B1, B2, 1)) { didHit = true; Hit = tempHit; }
		if (GetIntersection(L1.y - B2.y, L2.y - B2.y, L1, L2, tempHit, hitDis) && InBox(tempHit, B1, B2, 2)) { didHit = true; Hit = tempHit; }
		if (GetIntersection(L1.z - B2.z, L2.z - B2.z, L1, L2, tempHit, hitDis) && InBox(tempHit, B1, B2, 3)) { didHit = true; Hit = tempHit; }

		return didHit;
	}
public:
	static bool Raycast(Entity* source, Hit* hit, glm::vec3 start, glm::vec3 end, bool ignoreTriggers = true)
	{
		Entity* ent;
		hit->position = end;
		bool hasHit = false;
		float leastDistance = glm::length(end - start);
		glm::vec3 b1, b2, hitPos;
		for (uint32_t i = 0; i < source->entities->size(); i++)
		{
			ent = source->entities->at(i);
			if (ent->isAwake() && ent->collides)
			{
				if (ignoreTriggers && ent->isTrigger) { continue; }
				if (ent == source) { continue; }
				b1.x = ent->boundingBox.transform.position.x - ent->boundingBox.transform.scale.x;
				b2.x = ent->boundingBox.transform.position.x + ent->boundingBox.transform.scale.x;
				b1.y = ent->boundingBox.transform.position.y - ent->boundingBox.transform.scale.y;
				b2.y = ent->boundingBox.transform.position.y + ent->boundingBox.transform.scale.y;
				b1.z = ent->boundingBox.transform.position.z - ent->boundingBox.transform.scale.z;
				b2.z = ent->boundingBox.transform.position.z + ent->boundingBox.transform.scale.z;
				
				if (CheckLineBox(b1, b2, start, end, hitPos))
				{
					if (glm::length(hitPos - start) < leastDistance)
					{
						leastDistance = glm::length(hitPos - start);
						hasHit = true;
						hit->position = hitPos;
						hit->entHit = ent;
					}
				}
			}
		}
		return hasHit;
	}
};