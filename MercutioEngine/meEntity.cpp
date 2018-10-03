#include "stdafx.h"
#include "meEntity.h"
#include <math.h>

double Entity::RandReal()
{
	return random->random();
}

int Entity::RandInt(int min, int max)
{
	double rand = RandReal();
	rand *= max - min + 1;
	return (int)rand + min;
}

void Entity::RandSetSeed(uint32_t seed)
{
	random->rng.seed(seed);
}

void Entity::SetDeleteStatus(bool status)
{
	doNotDelete = status;
	for (uint32_t i = 0; i < children.size(); i++)
	{
		children[i]->SetDeleteStatus(status);
	}
}

void Entity::AddChild(Entity* child)
{
	children.push_back(child);
	child->parent = this;
}

void Entity::SetParent(Entity* parent)
{
	this->parent = parent;
	if (parent == nullptr) { return; }
	parent->children.push_back(this);
}

void Entity::SysUpdate()
{
	if (kinematic) { transform.position += physObject.velocity * (float)deltaTime; }
	boundingBox.transform.position = transform.position;
	//move child objects
	for (unsigned int i = 0; i < children.size(); i++)
	{
		//GetChild(i)->transform.position = transform.position + GetChild(i)->localTransform.position;
		glm::mat4 translateMatrix;
		GetChild(i)->localTransform.UpdateMatrix(translateMatrix);
		GetChild(i)->transform.rotation *= transform.rotation;
		glm::vec4 tempVec = (glm::vec4(GetChild(i)->localTransform.position, 1) * transform.GetRotation());
		GetChild(i)->transform.position = transform.position + glm::vec3(tempVec.x, tempVec.y, tempVec.z);/**/
	}
}

void Entity::SysFixedUpdate()
{
	//physObject.PsysUpdate();
}

Entity* Entity::Copy()
{
	//copy creates a new object based on another object and returns it. sub classes will write their own version
	Entity* copy = new Entity(*this);
	DeepCopy(this, copy);
	return copy;
}

void Entity::SetAwake(bool awakeState)
{
	privateWakeState = awakeState;
	SetAwakeRemote(awakeState);
}

void Entity::SetAwakeRemote(bool awakeState)
{
	awake = awakeState;
	for (uint32_t i = 0; i < children.size(); i++)
	{
		children[i]->SetAwakeRemote(awakeState);
	}
}

void Entity::DeepCopy(Entity* source, Entity* copy)
{
	//DeepCopy copies both the entity and its children.
	//Recursively walks the tree creating new objects as needed.
	copy->children.clear();
	copy->localTransform.position = source->localTransform.position;
	for (unsigned int i = 0; i < source->children.size(); i++)
	{
		copy->children.push_back(source->children[i]->Copy());
		copy->initQueue.push_back(copy->children.back());
		copy->children.back()->parent = this;
	}
}

Entity::Entity()
{
	initQueue = std::vector<Entity*>();
	boundingBox.transform.scale = transform.scale * 50.0f;
	boundingBox.transform.position = transform.position;
	children = std::vector<Entity*>();
	//Awake();
}

Entity::~Entity()
{

}

void Entity::Render(RenderData* data)
{
	if (materialPtr == nullptr || meshPtr == nullptr) { return; }
	materialPtr->UseMatrial();
	meshPtr->Bind();
	glUniformMatrix4fv(CAMERA_MATRIX_ATTRIB_LOCATION, 1, GL_FALSE, glm::value_ptr(data->viewMatrix));
	glUniformMatrix4fv(WORLD_MATRIX_ATTRIB_LOCATION, 1, GL_FALSE, glm::value_ptr(data->worldMatrix));
	glUniform1f(CURRENT_FRAME_LOCATION, currentFrame + 1.0f);
	glUniform1f(TOTAL_FRAMES_LOCATION, numFrames);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	if (collides)
	{
		//render collision box
		//set draw mode to gl_line
		//use debug shader
		/*if (debugShader == nullptr) { return; }
		glUseProgram(*debugShader);
		glUniformMatrix4fv(CAMERA_MATRIX_ATTRIB_LOCATION, 1, GL_FALSE, glm::value_ptr(*matrix));
		glUniform3f(TEXT_COLOR_UNIFORM_LOCATION, 1.0, 0.0, 0.0);*/
	}
}

void Entity::Bind()
{
	materialPtr->UseMatrial();
	meshPtr->Bind();
}

void Entity::DebugCircle(float radius, int sides)
{
	glm::vec3 thisVert;
	glm::vec3 nextVert;
	float angleDelta = (float)std::_Pi * 2.0f / (float)sides;
	float currentAngle = 0;
	//thisVert.x = radius;
	nextVert.x = radius;
	for (int i = 0; i < sides; i++)
	{
		thisVert = nextVert;
		currentAngle += angleDelta;
		nextVert.y = radius*std::sin(currentAngle);
		nextVert.x = radius*std::cos(currentAngle);
		debugVerts.push_back(thisVert);
		debugVerts.push_back(nextVert);
	}
}

void Entity::DebugRender(glm::mat4* matrix)
{
	glBegin(GL_LINES);
	glm::vec4 vert;
	for (uint32_t i = 0; i < debugVerts.size(); i++)
	{
		vert = glm::vec4(debugVerts[i],0);
		glVertex3f(vert.x, vert.y, vert.z);
	}
	glEnd();
}

void Entity::DebugLine(glm::vec3 pos0, glm::vec3 pos1)
{
	debugVerts.push_back(pos0);
	debugVerts.push_back(pos1);
}

void Entity::RemoveChild(int ind)
{
	GetChild(ind)->parent = nullptr;
	children.erase(children.begin() + ind);
}

Entity* Entity::GetChild(int ind)
{
	return children[ind];
}