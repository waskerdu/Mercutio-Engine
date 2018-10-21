#pragma once
#include "meEntity.h"
#include "meInput.h"
class Menu : public Entity
{
	bool supressInput = false;
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
	glm::vec3 blockedColor = glm::vec3(0.5f, 0.5f, 0.5f);
	std::string message = "";
	Message messageType = none;
	int visibleRows = 6;
	glm::vec3 tempPos;
private:
	void BumpUp();
	void BumpDown();
	void SetColors();
	void ChangeSelected(int bump);
public:
	Menu();
	~Menu();
	void Update();
	void Awake();
	void Reset();
	void SetChildPositions();
	void ResetPosition();
	Entity* Copy();

	void Clear();
};

