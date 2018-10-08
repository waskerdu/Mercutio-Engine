#pragma once
#include "meUIEntity.h"
#include <iostream>
#include <string>
#include <map>
#include "meCharacter.h"
#include "meMath.h"

class Text : public Entity
{
public:
	//ui stuff
	std::string text;
	std::string startText;
	std::string endText;
	std::vector<std::string> inserts;
	std::string message = "";
	std::string leftMessage = "leftMessage";
	std::string rightMessage = "rightMessage";
	std::string defaultText = "";
	bool blocked = false;
	int messagesSent = 0;
	float width = 0;
	float height = 20;
	int iter = 0;
	bool useIter = false;
	int maxVal = 0;
	int minVal = 0;
	bool loop = false;
	void Confirm();
	void Inc();
	void Dec();
private:
	void Bump();
public:

	//rendering
	std::map<GLchar, Character>* font;
	glm::vec3 color = glm::vec3(1);
	glm::vec2 textPos;
	bool useTextPos = false;
	GLuint VAO, VBO;
	GLuint* shader;
	void Render(RenderData* data);
	void SetText(std::string text) { this->text = defaultText + text; }
	Entity* Copy();

	Text();
	~Text();
};