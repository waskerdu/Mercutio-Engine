#pragma once
#include "meMath.h"
#include "meInputController.h"
#include "meVirtualAxis.h"
#include "meVirtualButton.h"
#include <vector>
#include <map>
#include "meControllerData.h"
#include <string>

namespace Input
{

	class InputMaster
	{
		std::vector<VirtualAxis*> virtualAxes;
		std::map<std::string, int> axisMap;
		std::vector<VirtualButton*> virtualButtons;
		std::map<std::string, int> buttonMap;
		std::vector<int> controllerOrder;
		std::vector<ControllerData*> controllerData;
		int axesCount;
		int buttonCount;
		const float *axisData;
		const unsigned char *buttonData;
		void RebuildAggregate();
		const int maxControllers = 4;
		const int numAxes = 12;
		const int numButtons = 18;
	public:
		std::vector<InputController*> controllers;
		InputController aggregate;
		InputController mkController;
		InputMaster();
		~InputMaster();
		void Update(double deltaTime, GLFWwindow* window);

		void BuildControllers();

		void AddButton(std::string alias);
		InputButton* GetButton(std::string alias);
		void ButtonAddKey(std::string alias);
		void ButtonAddJoyButton(std::string alias, bool dualShock);
		void ButtonAddJoyAxis(std::string alias, bool dualShock);
		void ButtonAddMouseAxis(std::string alias);

		void AddAxis(std::string alias);
		InputAxis* GetAxis(std::string alias);
		void AxisAddKey(std::string alias);
		void AxisAddJoyButton(std::string alias, bool dualShock);
		void AxisAddJoyAxis(std::string alias, bool dualShock);
		void AxisAddMouseAxis(std::string alias);

		void AddAxis2(std::string alias);
		InputAxis2* GetAxis2(std::string alias);
		void Axis2AddKey(std::string alias, bool xAxis);
		void Axis2AddJoyButton(std::string alias, bool dualShock, bool xAxis);
		void Axis2AddJoyAxis(std::string alias, bool dualShock, bool xAxis);
		void Axis2AddMouseAxis(std::string alias, bool xAxis);
	};

}