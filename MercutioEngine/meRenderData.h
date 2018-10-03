#pragma once
#include "meMath.h"
struct RenderData
{
	glm::mat4 viewMatrix;
	glm::mat4 worldMatrix;
	float frame = 0;
	float numberOfFrames = 1;
	//room for more
};