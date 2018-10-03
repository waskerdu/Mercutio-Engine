#pragma once
#include <iostream>
#include <string>
#define GLEW_STATIC
#include <GL\glew.h>
#include <GL\GL.h>
#include <GLFW\glfw3.h>
#include <vector>
#include "meControllerData.h"

namespace Input
{

	enum ButtonFireMethod
	{
		push,
		release,
		hold
	};

	enum ButtonType
	{
		key,
		button,
		axis,
		mouseButton
	};

	class VirtualButton
	{
		//virtualButton. vbuttons read from a single input type
		double heldTime = 0;
		bool firing = false;
	public:
		ButtonType type;
		ButtonFireMethod fireType;
	    double axisThreshold = 0;
		bool invertAxis = false;
		int index = 0;
		double initalDelay = -1;
		double requiredTimeHeld = -1;
		double maximumTimeHeld = -1;
		bool delayed = false;
		int controllerIndex = 0;
	public:
		VirtualButton(ButtonType buttonType, ButtonFireMethod fireType, int index, double initalDelay, double requiredTimeHeld, double maximumTimeHeld);
		VirtualButton(ButtonType buttonType, ButtonFireMethod fireType, int index, double initalDelay, double requiredTimeHeld, double maximumTimeHeld, double axesThreshold, bool invertAxis);
		~VirtualButton();
		//void Update(double deltaTime, GLFWwindow* window, std::vector<const float*>* axisData, std::vector< const unsigned char*>* buttonData);
		void Update(std::vector<ControllerData*>* controllerData);
		bool isFiring();
	};

}