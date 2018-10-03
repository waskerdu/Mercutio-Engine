#pragma once
#include "meInput.h"

class GameController
{
	/*std::vector<Button> buttons;
	std::vector<Axis> axes;
	std::vector<Axis2> axes2;*/
	
	bool fire1 = false;
	bool fire1Pressed = false;
	bool fire1Released = false;
	int fire1Axis = 0;

	bool fire2 = false;
	bool fire2Pressed = false;
	bool fire2Released = false;
	int fire2Axis = 1;

	bool fire3 = false;
	bool fire3Pressed = false;
	bool fire3Released = false;
	int fire3Axis = 2;

	bool fire4 = false;
	bool fire4Pressed = false;
	bool fire4Released = false;
	int fire4Axis = 3;


	void Update()
	{
		//fire1=bu
	}
};