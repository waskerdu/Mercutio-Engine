#pragma once
#define GLEW_STATIC
#include <GL\glew.h>
#include <GL\GL.h>
#include <GLFW\glfw3.h>
#include <iostream>
//mercutio uses various clocks for its subsystems
//deltaTime is the time since last frame. clock update is only called within the main engine loop

class Clock
{
	double deltaTime = 0;
	double lastTime = 0;
	double currentTime = 0;
public:
	double GetDeltaTime() { return deltaTime; }
	void Update()
	{
		currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;
	}
};