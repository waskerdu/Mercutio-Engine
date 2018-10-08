#pragma once
#include <GLFW\glfw3.h>

struct MonitorMode
{
	enum WindowMode
	{
		windowed,
		fullscreen,
		borderlessFullscreen
	};
	GLFWwindow* window;
	int windowWidth = 1920;
	int windowHeight = 1080;
	int viewWidth = 1920;
	int viewHeight = 1080;
	WindowMode windowMode = borderlessFullscreen;
	int monitorIndex = 0;
	GLFWmonitor* monitor;
	int vsync = 0;
	int framerateCap = -1;
};