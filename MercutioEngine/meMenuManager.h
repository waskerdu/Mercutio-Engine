#pragma once
#include "meEntity.h"
#include "meMenu.h"
class MenuManager :
	public Entity
{
public:
	MenuManager();
	~MenuManager();
	void CreateMenus(std::string){}
};

