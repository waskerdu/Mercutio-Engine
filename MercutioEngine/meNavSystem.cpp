#include "stdafx.h"
#include "meNavSystem.h"

bool NavSystem::atNode(glm::vec3 pos)
{
	return glm::length(pos - GetNode()) < closeEnough;
}

glm::vec3 NavSystem::GetNode()
{
	return navPath[navNode];
}

glm::vec3 NavSystem::GetNode(glm::vec3 pos)
{
	if (atNode(pos))
	{
		if (forward) { navNode++; }
		else { navNode--; }
		if (navNode == navPath.size()) { navNode = 0; }
		if (navNode == -1) { navNode = (int)navPath.size() - 1; }
	}
	return navPath[navNode];
}

NavSystem::NavSystem()
{
}


NavSystem::~NavSystem()
{
}
