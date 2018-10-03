#pragma once
#include <vector>
#define GLEW_STATIC
#include <GL\glew.h>
#include <GL\GL.h>
#include <GLFW\glfw3.h>
struct ControllerData
{
	const float* axisData;
	const unsigned char* buttonData;
	int axisCount;
	int buttonCount;
	double deltaTime = 0;
	GLFWwindow* window;
	ControllerData()
	{

	}
	~ControllerData()
	{

	}
	void Update(double deltaTime, GLFWwindow* window, int controllerIndex)
	{
		this->deltaTime = deltaTime;
		this->window = window;
		axisData = glfwGetJoystickAxes(controllerIndex, &axisCount);
		buttonData = glfwGetJoystickButtons(controllerIndex, &buttonCount);
		/*if (controllerIndex == 0)
		{
			std::cout << axisData[0] << "\n";
		}*/
	}
	float GetAxis(int index)
	{
		if (axisCount == 0) { return 0; }
		if (index < axisCount) { return axisData[index]; }
		else { return 0; }
	}
	bool GetButton(int index)
	{
		if (buttonCount == 0) { return false; }
		if (index < buttonCount) { return buttonData[index] == GLFW_PRESS; }
		else { return false; }
	}
};