#pragma once
#include <vector>
#include "meMath.h"
class NavSystem
{
public:
	std::vector<glm::vec3> navPath;
	int navNode = 0;
	double closeEnough = 10;
	bool forward = true;
	bool atNode(glm::vec3 pos);
	glm::vec3 GetNode();//gets the current node. does not change state of nav system
	glm::vec3 GetNode(glm::vec3 pos);//gets the current node. if position is close enough go to next node
	void SetNodeToNearest(glm::vec3 pos);//iterates through nav path and sets navNode to closest node
	NavSystem();
	~NavSystem();
};

