#pragma once
#include "meEntity.h"
#include <map>
#include "meMenu.h"
#include "meText.h"
class MenuManager :
	public Entity
{
	Menu* currentMenu;
	std::vector<Menu*> visitedMenus;
	std::map<std::string, Menu*> menus;
public:
	std::map<GLchar, Character>* titleFont;
	//std::map<GLchar, Character>* textFont;
	Text* text;
	Menu* menu;
	Menu* newMenu;
	Text* newText;
	Entity* sceneManager;
private:
	void SelectChildren();
public:
	MenuManager();
	~MenuManager();
	std::string GetCurrentMenu() { return currentMenu->alias; }
	void CreateMenus(std::string str = "other.txt");
	void SelectMenu(std::string name);
	void SelectPreviousMenu();
	void Update();
	void SendMessage(std::string message, Entity* ent);
	void AddText(std::string menu, std::string text, std::string message, std::string leftMessage = "leftMessage", std::string rightMessage = "rightMessage");
	void AddImage(std::string menu, Entity* ent);
	Text* GetText(std::string menu, std::string alias);
	void RemoveChildTexts(std::string menu, std::string ignore = "none");
};

