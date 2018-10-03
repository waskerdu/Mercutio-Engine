#pragma once

#define GLEW_STATIC
#include <GL\glew.h>
#include <GL\GL.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include "meMath.h"
#include "meWorld.h"
#include "meCharacter.h"
#include "meCamera.h"
#include "meRenderData.h"
#include <map>

class Renderer
{
	GLFWwindow* window;
	bool needsInit = true;
	bool useLayeredRendering = true;
	glm::mat4 debugMatrix;
	World* worldPtr;
	glm::mat4 camMatrix;
	glm::mat4 viewMatrix;
	std::map<GLchar, Character> Characters;
	RenderData data;
	void Init();
	GLuint VAO, VBO;
	//works?
	//void RenderText(Shader &shader, std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);

public:
	bool debug = false;
	GLuint* debugShader;
	Renderer(World* worldPtr, GLFWwindow* window);
	~Renderer();
	void SetWindow(GLFWwindow* window) { this->window = window; }
	void Update(Camera* camera);
	void RenderLayered(Camera* camera);
	//void RenderZBuffer(Camera* camera);
	void SetRenderLayered(bool useLayeredRendering);
};