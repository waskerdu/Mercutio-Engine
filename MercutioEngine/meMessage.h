#pragma once
#include <string>
struct Message
{
	std::string name = "";
	float val = 0;
	Message(){}
	Message(std::string name) { this->name = name; }
	Message(std::string name, float val) { this->name = name; this->val = val; }
};