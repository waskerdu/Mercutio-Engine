#pragma once
#include <string>
#define GLEW_STATIC
#include <GL\glew.h>
#include <GL\GL.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <vector>
#include "meControllerData.h"

namespace Input
{

	enum AxisType
	{
		deltaMouseX,
		deltaMouseY,
		mouseX,
		mouseY,
		joystickAxis,
		joystickButton,
		keyButton
	};
	
	class VirtualAxis
	{
		/*
		Virtual Axes draw from raw buttons and raw axes. They offer no processing or higher level functionality. That is what the InputAxis class is for
		Valid type names are mouseX, mouseY, joystickAxis, joystickButton, keyButton
		*/
		bool usesButtons = false;
		int axisIndex;
		int buttonIndexPos;
		int buttonIndexNeg;
		double value;
		double lastPos = 0;
		AxisType type;
	public:
		bool inverted = false;
		int controllerIndex = 0;
		VirtualAxis(AxisType type);
		VirtualAxis(AxisType type, int axisIndex);
		VirtualAxis(AxisType type, int buttonIndexPos, int buttonIndexNeg);//axis from buttons. use negative indicies to make pos or neg buttons optional
		~VirtualAxis();
		//void Update(double deltaTime, GLFWwindow* window, std::vector<const float*>* axisData, std::vector< const unsigned char*>* buttonData);
		void Update(std::vector<ControllerData*>* controllerData);
		double GetValue();
	};

}

