#pragma once
#define GLEW_STATIC
#include <GL\glew.h>
#include <GL\GL.h>
#include <GLFW\glfw3.h>
#include "assets\shaders\preamble.glsl"
#include "meRenderData.h"

struct Material
{
	GLuint texture;
	unsigned char* textureData;
	GLuint* shaderProgram;

	Material(GLuint texture, GLuint* shaderProgram)
	{
		this->texture = texture;
		this->shaderProgram = shaderProgram;
		glBindTexture(GL_TEXTURE_2D, texture);

		glUseProgram(*shaderProgram);
		glUniform1i(TEXTURE_UNIFORM_LOCATION, 0);
	}

	void UseMatrial()
	{
		glUseProgram(*shaderProgram);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		
	}
};