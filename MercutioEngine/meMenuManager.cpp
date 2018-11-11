#include "stdafx.h"
#include "meMenuManager.h"
#include <fstream>
#include "meParser.h"

MenuManager::MenuManager()
{
}


MenuManager::~MenuManager()
{
}

void MenuManager::AddImage(std::string menu, Entity* ent)
{
	//
	Menu* currentMenu = menus[menu];
}

Text* MenuManager::GetText(std::string menu, std::string alias)
{
	Menu* currentMenu = menus[menu];
	for (size_t i = 0; i < currentMenu->children.size(); i++)
	{
		if (currentMenu->children[i]->alias == alias)
		{
			return dynamic_cast<Text*>(currentMenu->children[i]);
		}
	}
	std::cout << "no text of alias " << alias << " found.";
	return nullptr;
}

void MenuManager::AddText(std::string menu, std::string text_str, std::string message, std::string leftMessage, std::string rightMessage)
{
	Menu* currentMenu = menus[menu];
	newText = dynamic_cast<Text*>(text->Copy());
	initQueue.push_back(newText);
	newText->SetParent(currentMenu);
	newText->text = text_str;
	newText->message = message;
	newText->leftMessage = leftMessage;
	newText->rightMessage = rightMessage;/**/
	currentMenu->SetChildPositions();
	newText->SetAwake(false);
}

void MenuManager::RemoveChildTexts(std::string menu, std::string ignore)
{
	Menu* currentMenu = menus[menu];
	std::vector<Entity*> tempChildren;
	for (size_t i = 0; i < currentMenu->children.size(); i++)
	{
		if (currentMenu->children[i]->alias == ignore || (int)i < currentMenu->lowestIndex)
		{ 
			tempChildren.push_back(currentMenu->children[i]);
			continue; 
		}
		currentMenu->children[i]->parent = nullptr;
		currentMenu->children[i]->SetAwake(false);
		currentMenu->children[i]->DeleteOnReset(true);
	}
	currentMenu->children.clear();
	currentMenu->children = tempChildren;
}

void MenuManager::SendMessage(std::string message, Entity* ent)
{
	sceneManager->SendMessage(message, ent);
	//std::cout << message << "\n";
}

void MenuManager::CreateMenus(std::string str)
{
	std::fstream file;
	std::string line;
	std::vector<std::string> parsedLine;
	newMenu = new Menu();
	newText = new Text();
	delete(newMenu);
	delete(newText);
	bool inComment = false;

	file.open(str.c_str());
	if (!file.is_open())
	{
		std::cout << "File " << str << " failed to open.\n";
		return;
	}

	while (std::getline(file, line))
	{
		Parser(line, parsedLine);
		if (parsedLine.size() == 0) { continue; }
		if (parsedLine[0][0] == '*') { inComment = !inComment; }
		if (inComment) { continue; }

		if (parsedLine[0] == "#Menu")
		{
			newMenu = dynamic_cast<Menu*>(menu->Copy());
			initQueue.push_back(newMenu);
			newMenu->SetParent(this);
			newMenu->DeleteOnReset(false);
			menus[parsedLine[1]] = newMenu;
			newMenu->alias = parsedLine[1];
			if (parsedLine[1] == "main") { currentMenu = newMenu; }
		}
		else if (parsedLine[0] == "#Text" || parsedLine[0] == "#Title")
		{
			if(newMenu==nullptr)
			{
				std::cout << "No menu defined for " << parsedLine[1] << ".\n";
				continue;
			}
			newText = dynamic_cast<Text*>(text->Copy());
			initQueue.push_back(newText);
			newText->SetParent(newMenu);
			newText->text = "";
			for (size_t i = 1; i < parsedLine.size(); i++)
			{
				newText->text += parsedLine[i] + " ";
			}
			newText->DeleteOnReset(false);
			//std::cout << newText->text << "\n";
			if (parsedLine[0] == "#Title") 
			{ 
				newMenu->lowestIndex++; 
				newMenu->selectedIndex++;
				newText->font = titleFont;
			}
		}
		else if (parsedLine[0] == "Message")
		{
			//std::cout << parsedLine[1] << "\n";
			if (newText == nullptr)
			{
				std::cout << "No text defined for " << parsedLine[1] << ".\n";
				continue;
			}
			//std::cout << parsedLine[1] << "\n";
			newText->message = parsedLine[1];
			if (parsedLine.size() > 2)
			{
				newText->leftMessage  = parsedLine[2];
				newText->rightMessage = parsedLine[3];
				//std::cout << parsedLine[1] << " grrrrraaaaa " << parsedLine[3] << "\n";
			}
		}
		else if (parsedLine[0] == "Alias")
		{
			if (newText == nullptr)
			{
				std::cout << "No text defined for " << parsedLine[1] << ".\n";
				continue;
			}
			newText->alias = parsedLine[1];
		}
	}
	//SelectChildren();
	//SelectMenu("gameOver");
}

void MenuManager::SelectMenu(std::string name)
{
	if (menus.count(name) == 0)
	{
		std::cout << "No menu of name " << name << " exists.\n";
		return;
	}
	currentMenu = menus[name];
	//if a menu is selected that has been previously selected
	//remove all visited menus after that
	bool popping = false;
	for (size_t i = 0; i < visitedMenus.size(); i++)
	{
		if (popping) { visitedMenus.pop_back(); }
		else if (visitedMenus[i] == currentMenu) { popping = true; }
	}
	if (popping == false) { visitedMenus.push_back(currentMenu); }
	SelectChildren();
}

void MenuManager::SelectPreviousMenu()
{
	if (visitedMenus.size() == 1) { return; }
	visitedMenus.pop_back();
	currentMenu->ResetPosition();
	currentMenu = visitedMenus[visitedMenus.size() - 1];
	SelectChildren();
}

void MenuManager::Update()
{
	//transmit messages to scene manager from current menu
}

void MenuManager::SelectChildren()
{
	currentMenu->SetAwake(true);
	for (size_t i = 0; i < children.size(); i++)
	{
		if (children[i] != currentMenu)
		{
			children[i]->SetAwake(false);
		}
	}
}