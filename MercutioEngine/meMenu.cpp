#include "stdafx.h"
#include "meMenu.h"
#include "meText.h"


Menu::Menu()
{
}


Menu::~Menu()
{
}

Entity* Menu::Copy()
{
	//copy creates a new object based on another object and returns it. sub classes will write their own version
	Menu* copy = new Menu(*this);
	DeepCopy(this, copy);
	return copy;
}

void Menu::Awake()
{
	SetColors();
	for (uint32_t i = 0; i < children.size(); i++)
	{
		GetChild(i)->localTransform.position.y = i * -(float)spacing;
	}
	message = GetChild(selectedIndex)->alias;
	supressInput = true;
}

void Menu::ChangeSelected(int bump)
{
	selectedIndex += bump;
	for (size_t i = 0; i < children.size(); i++)//will only try to find a valid selected index so many times
	{
		if (loopSelection)
		{
			if (selectedIndex < lowestIndex) { selectedIndex = (int)children.size() - 1; }
			else if (selectedIndex == children.size()) { selectedIndex = lowestIndex; }
		}
		else
		{
			if (selectedIndex < lowestIndex) { selectedIndex = lowestIndex; }
			else if (selectedIndex == children.size()) { selectedIndex = (int)children.size() - 1; }
		}
		if (dynamic_cast<Text*>(GetChild(selectedIndex))->blocked == false) { break; }
		selectedIndex += bump;
	}
	SetColors();
}

void Menu::SetColors()
{
	for (uint32_t i = lowestIndex; i < children.size(); i++)
	{
		//children[i]
		if (i == selectedIndex)
		{
			dynamic_cast<Text*>(children[i])->color = selectedColor;
		}
		else if (dynamic_cast<Text*>(children[i])->blocked)
		{
			dynamic_cast<Text*>(children[i])->color = blockedColor;
		}
		else
		{
			dynamic_cast<Text*>(children[i])->color = defaultColor;
		}
	}
}

void Menu::BumpUp()
{
	//selectedIndex--;
	ChangeSelected(-1);
}

void Menu::BumpDown()
{
	//selectedIndex++;
	ChangeSelected(1);
}

void Menu::Reset()
{
	Clear();
}

void Menu::Clear()
{
	messageType = none;
}

void Menu::Update()
{
	if (controller == nullptr)
	{
		std::cout << "menu has no attached controller\n";
		return;
	}
	if (supressInput)
	{
		supressInput = false;
		return;
	}
	if (controller->GetButton("menuDown"))
	{
		BumpDown();
	}
	if (controller->GetButton("menuUp"))
	{
		BumpUp();
	}
	if (controller->GetButton("menuLeft"))
	{
		messageType = left;
		parent->SendMessage(dynamic_cast<Text*>(GetChild(selectedIndex))->leftMessage, GetChild(selectedIndex));
	}
	if (controller->GetButton("menuRight"))
	{
		parent->SendMessage(dynamic_cast<Text*>(GetChild(selectedIndex))->rightMessage, GetChild(selectedIndex));
	}
	if (controller->GetButton("menuConfirm"))
	{
		parent->SendMessage(dynamic_cast<Text*>(GetChild(selectedIndex))->message, GetChild(selectedIndex));
	}
}