#pragma once
#include "meVirtualAxis.h"
#include <vector>

namespace Input
{
	class InputAxis
	{
		friend class InputMaster;
		friend class InputController;
		std::vector<int> axisIndices;
		std::vector<VirtualAxis*>* virtualAxes;
	public:
		InputAxis();
		~InputAxis();
		double GetValue();
	};
}

