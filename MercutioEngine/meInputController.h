#pragma once
#define GLEW_STATIC
#include <GL\glew.h>
#include <GL\GL.h>
#include <GLFW\glfw3.h>
#include "meMath.h"
#include <vector>
#include "meInputAxis.h"
#include "meInputAxis2.h"
#include "meInputButton.h"

namespace Input
{
	class InputController
	{
		//std::vector<InputAxis2*> sticks;
		//std::vector<InputButton*> buttons;

		friend class InputMaster;
		void SetXbox(int startAxis, int startButton);
		void SetDualShock(int startAxis, int startButton);
		void SetVirtualVectors(std::vector<VirtualButton*>* virtualButtons, std::vector<VirtualAxis*>* virtualAxes);
		std::vector<VirtualButton*>* virtualButtons;
		std::vector<VirtualAxis*>* virtualAxes;
		bool connected = false;
	public:
		InputAxis2 mousePosition;
		InputAxis2 rightStick;
		InputAxis2 leftStick;
		InputButton menuUp;
		InputButton menuDown;
		InputButton menuLeft;
		InputButton menuRight;
		InputButton menuConfirm;
		InputButton menuCancel;
		InputButton menuToggle;
		InputButton roll;
		InputController();
		~InputController();
	};
}
