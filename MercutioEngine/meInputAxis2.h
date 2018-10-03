#pragma once
#include <vector>
#include "meVirtualAxis.h"
#include "meMath.h"
namespace Input
{
	class InputAxis2
	{
		friend class InputMaster;
		friend class InputController;
		std::vector<int> xAxisIndices;
		std::vector<int> yAxisIndices;
		std::vector<VirtualAxis*>* virtualAxes;
	public:
		bool invertX = false;
		bool invertY = false;
		bool clamp = true;
		double deadZone = 0.5;
		bool smooth = false;
		InputAxis2();
		~InputAxis2();
		glm::vec2 GetValue();
	};
}
