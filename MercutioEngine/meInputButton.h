#pragma once
#include "meVirtualButton.h"
#include <vector>

namespace Input
{
	class InputButton
	{
		std::vector<int> buttonIndices;//virtual button pointers only public for external initalization. may make a friend class later
		friend class InputMaster;
		friend class InputController;
		std::vector<VirtualButton*>* virtualButtons;
	public:
		InputButton();
		~InputButton();
		bool isFiring();
	};
}
