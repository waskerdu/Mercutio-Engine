#pragma once

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <math.h>

struct Rect
{
public:
	float width = 0;
	float height = 0;
	float posX = 0;
	float posY = 0;
	Rect(float _width, float _height, float _posX, float _posY)
	{
		width = _width;
		height = _height;
		posX = _posX;
		posY = _posY;
	}
};