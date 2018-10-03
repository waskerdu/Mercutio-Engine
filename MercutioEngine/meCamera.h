#pragma once
#include "meMath.h"
#include "mePhysics.h"
#include "meEntity.h"
#include "meInput.h"
#include <vector>

class Camera : public Entity
{
public:
	bool usePerspective = false;
	glm::mat4 matrix = glm::mat4();
	Rect rect = Rect(800, 600, 0, 0);
	float near = 0.1f;
	float far = 100.0f;
	float baseZoom = 0.5;
	float zoom = 0.5f;
	float vFov = 45.0f;
	float speed = 300.0f;
	float baseScreenHeight = 1080.0f;
	std::vector<Entity*> targets;
	InputManager* input;
	glm::vec3 targetPosition;

	void Reset()
	{
		physObject.velocity *= 0;
	}

	//glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);

	void Update()
	{
		//std::cout << transform.position.x << " " << transform.position.y << " " << " " << transform.position.z << "\n";
		if (targets.size() > 0)
		{
			targetPosition *= 0;
			int numAwake = 0;
			for (uint32_t i = 0; i < targets.size(); i++)
			{
				if (targets[i]->isAwake())
				{
					targetPosition += targets[i]->transform.position;
					numAwake++;
				}
			}
			if (numAwake > 0)
			{
				targetPosition.x = targetPosition.x / numAwake;
				targetPosition.y = targetPosition.y / numAwake;
				targetPosition.z = transform.position.z;
				physObject.velocity = targetPosition - transform.position;
			}
			else
			{
				physObject.velocity *= 0;
			}
		}
		zoom = baseZoom*windowHeight / baseScreenHeight;
	}
	
	void BuildMatrix()
	{
		if (usePerspective) 
		{ 
			matrix = glm::perspective(glm::radians(vFov/zoom), windowWidth / windowHeight, near, far); 
		}
		else 
		{ 
			matrix = glm::ortho(0.0f, windowWidth/zoom, 0.0f, windowHeight/zoom, 0.1f, 100.0f); 
		}
		//rotate then move
		/*matrix = glm::rotate(matrix, eulerAngles.z, glm::vec3(0, 0, 1));
		matrix = glm::rotate(matrix, eulerAngles.y, glm::vec3(0, 1, 0));
		matrix = glm::rotate(matrix, eulerAngles.x, glm::vec3(1, 0, 0));*/
		//matrix = glm::translate(matrix, -transform.position);
	}
	//glm::vec3 GetEulerAngles() { return eulerAngles; }
	//void SetEulerAngles(glm::vec3 _eulerAngles) { eulerAngles = _eulerAngles; }
	glm::mat4 GetMatrix() 
	{ 
		BuildMatrix();
		glm::vec3 offset = -transform.position;
		offset.x += windowWidth*0.5f/zoom;
		offset.y += windowHeight*0.5f/zoom;
		return glm::translate(matrix, offset);
		return matrix;
	}
};