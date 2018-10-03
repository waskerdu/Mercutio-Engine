#pragma once
#include "meMath.h"
#include <GLFW\glfw3.h>

struct Character
{
	GLuint     textureID;  // ID handle of the glyph texture
	glm::ivec2 Size;       // Size of glyph
	glm::ivec2 Bearing;    // Offset from baseline to left/top of glyph
	GLuint     Advance;    // Offset to advance to next glyph
};