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
}

void Menu::ChangeSelected()
{
	if (loopSelection)
	{
		if (selectedIndex < lowestIndex) { selectedIndex = children.size() - 1; }
		else if (selectedIndex == children.size()) { selectedIndex = lowestIndex; }
	}
	else
	{
		if (selectedIndex < lowestIndex) { selectedIndex = lowestIndex; }
		else if (selectedIndex == children.size()) { selectedIndex = children.size() - 1; }
	}
	message = GetChild(selectedIndex)->alias;
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
		else
		{
			dynamic_cast<Text*>(children[i])->color = defaultColor;
		}
	}
}

void Menu::BumpUp()
{
	//std::cout << "menu bump up\n";
	selectedIndex--;
	ChangeSelected();
}

void Menu::BumpDown()
{
	//std::cout << "menu bump down\n";
	//if (selectedIndex < lowestIndex) { selectedIndex = children.size() - 1; }
	selectedIndex++;
	ChangeSelected();
}

bool Menu::FindMessage(std::string text, Message mess)
{
	/*for (int i = 0; i < messages.size(); i += 1)
	{
		if ((messages[i].first == text) && (messages[i].second == mess))
		{
			return true;
		}
	}
	return false;*/
	if (text == message&&mess == messageType)
	{
		Clear();
		return true;
	}
	return false;
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
		//std::pair<std::string, Message> mess;
		//mess.first = GetChild(selectedIndex)->alias;
		//mess.second = left;
		messageType = left;
		//messages.push_back(mess);/**/
		//std::cout << "left\n";
	}
	if (controller->GetButton("menuRight"))
	{
		//std::cout << "right\n";
		//std::pair<std::string, Message> mess;
		//mess.first = GetChild(selectedIndex)->alias;
		//mess.second = right;
		messageType = right;
		//messages.push_back(mess);/**/
	}
	if (controller->GetButton("menuConfirm"))
	{
		//std::cout << "confirm\n";
		//std::pair<std::string, Message> mess;
		//mess.first = GetChild(selectedIndex)->alias;
		//mess.second = confirm;
		messageType = confirm;
		//messages.push_back(mess);/**/
	}
}