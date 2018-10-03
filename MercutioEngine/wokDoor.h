#pragma once
#include "meEntity.h"
class Door :
	public Entity
{
	glm::vec3 openPos;
	glm::vec3 closedPos;
	glm::vec3 targetPos;
	float speed = 300.0f;
	float closeEnough = 10.0f;
public:
private:
public:
	Door();
	~Door();
	void Open() { targetPos = openPos; }
	void Close() { targetPos = closedPos; }
	void SetOpen() { transform.position = openPos; targetPos = openPos; }
	void SetClosed() { transform.position = closedPos; targetPos = closedPos; }
	void SetOpenPos(glm::vec3 openPos) { this->openPos = openPos; }
	void SetClosedPos(glm::vec3 closedPos) { this->closedPos = closedPos; }
	void SendMessage(std::string message);
	void Update();
	void OnCollision(Entity* ent);
	void SetSpeed(float speed) { this->speed = speed; }
	Entity* Copy();
};

