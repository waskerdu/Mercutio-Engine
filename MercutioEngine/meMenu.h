#pragma once
#include "meEntity.h"
#include "meInput.h"
class Menu : public Entity
{
public:
	enum Message
	{
		confirm,
		left,
		right,
		none
	};
	InputController* controller;
	int lowestIndex = 1;
	int selectedIndex = 1;
	bool loopSelection = true;
	double spacing = 200;
	glm::vec3 defaultColor;
	glm::vec3 selectedColor = glm::vec3(1, 1, 1);
	std::string message = "";
	Message messageType = none;
	//std::vector<std::pair<std::string, Message>> messages;
	
private:
	void BumpUp();
	void BumpDown();
	void SetColors();
	void ChangeSelected();
public:
	Menu();
	~Menu();
	void Update();
	void Awake();
	void Reset();
	Entity* Copy();
	bool FindMessage(std::string text, Message mess);
	void Clear();
};

