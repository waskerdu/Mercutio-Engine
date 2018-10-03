#pragma once
#include "meEntity.h"
class NavNode :
	public Entity
{
	std::vector<NavNode*> visibleNodes;
public:
	enum Type
	{
		none
	};
	Type type = none;
private:
public:
	void Update();
	Entity* Copy()
	{
		NavNode* copy = new NavNode(*this);
		DeepCopy(this, copy);
		return copy;
	}
	NavNode();
	~NavNode();
};

