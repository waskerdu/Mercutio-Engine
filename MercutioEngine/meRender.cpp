#include "stdafx.h"
#include "meRender.h"

#include <ft2build.h>
#include FT_FREETYPE_H

Renderer::Renderer(World* worldPtr, GLFWwindow* window)
{
	this->worldPtr = worldPtr;
	this->window = window;
	Init();
	//glEnable(GL_DEPTH_TEST);
	//glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 3, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(POSITION_ATTRIB_LOCATION);
	glVertexAttribPointer(POSITION_ATTRIB_LOCATION, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	//glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	SetRenderLayered(true);
}

Renderer::~Renderer()
{

}

void Renderer::Init()
{
	/*glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
	glm::mat4 trans;
	trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
	vec = trans * vec;*/
	//std::cout << vec.x << vec.y << vec.z << std::endl;
	needsInit = false;
}

void Renderer::RenderLayered(Camera* camera)
{
	if (needsInit) { Init(); }
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glm::mat4 scaleMatrix;
	//glm::vec3 trans = -camera->transform.position;
	//trans.x += width*0.5;
	//trans.y += height*0.5;
	//camMatrix = glm::ortho(0.0f, (float)width, 0.0f, (float)height, 0.1f, 100.0f);

	//camMatrix = glm::translate(camMatrix, trans);
	camMatrix = camera->GetMatrix();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_BLEND); 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	//glDisable(GL_DEPTH_TEST);
	for each (std::vector<Entity*> layer in worldPtr->layers)
	{
		for each (Entity* entPtr in layer)
		{
			if (entPtr->isAwake() == false) { continue; }
			if (entPtr->isVisible == false) { continue; }
			//viewMatrix = camMatrix * entPtr->transform.GetMatrix();
			
			scaleMatrix = glm::mat4();
			scaleMatrix = glm::scale(scaleMatrix, entPtr->transform.scale);
			//data.worldMatrix = entPtr->transform.GetMatrix();
			data.worldMatrix = scaleMatrix;
			data.viewMatrix = camMatrix * entPtr->transform.GetMatrix();

			//entPtr->Render(&viewMatrix, nullptr);
			entPtr->Render(&data);
			if (debug && entPtr->collides)
			{
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				glUseProgram(*debugShader);
				debugMatrix = glm::translate(camMatrix, entPtr->boundingBox.transform.position);
				glUniformMatrix4fv(CAMERA_MATRIX_ATTRIB_LOCATION, 1, GL_FALSE, glm::value_ptr(debugMatrix));
				glUniform3f(TEXT_COLOR_UNIFORM_LOCATION, entPtr->boundingBox.debugColor.r, entPtr->boundingBox.debugColor.g, entPtr->boundingBox.debugColor.b);
				glBindVertexArray(VAO);
				GLfloat vertices[6][3] =
				{
					{ -entPtr->boundingBox.transform.scale.x, entPtr->boundingBox.transform.scale.y, 0 },
					{ -entPtr->boundingBox.transform.scale.x, -entPtr->boundingBox.transform.scale.y, 0 },
					{ entPtr->boundingBox.transform.scale.x, -entPtr->boundingBox.transform.scale.y, 0 },

					{ -entPtr->boundingBox.transform.scale.x, entPtr->boundingBox.transform.scale.y, 0 },
					{ entPtr->boundingBox.transform.scale.x, -entPtr->boundingBox.transform.scale.y, 0 },
					{ entPtr->boundingBox.transform.scale.x, entPtr->boundingBox.transform.scale.y, 0 },
				};
				glBindBuffer(GL_ARRAY_BUFFER, VBO);
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
				glBindBuffer(GL_ARRAY_BUFFER, 0);
				glDrawArrays(GL_TRIANGLES, 0, 6);
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
			if (debug)
			{
				entPtr->DebugRender(&viewMatrix);
			}
		}
	}
	glBindVertexArray(0);
	/*glfwSwapInterval(1);
	glfwSwapBuffers(window);
	glfwPollEvents();*/
}

/*void Renderer::RenderZBuffer(Camera* camera)
{
	if (needsInit) { Init(); }
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	//glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	//glm::vec3 trans = -camera->transform.position;
	//trans.x += width*0.5;
	//trans.y += height*0.5;
	//camMatrix = glm::ortho(0.0f, (float)width, 0.0f, (float)height, 0.1f, 100.0f);

	//camMatrix = glm::translate(camMatrix, trans);
	camMatrix = camera->GetMatrix();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for each (Entity* entPtr in worldPtr->entities)
	{
		if (entPtr->isAwake() == false) { continue; }
		viewMatrix = camMatrix * entPtr->transform.GetMatrix();
		entPtr->Render(&viewMatrix);
		if (debug && entPtr->collides)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glDisable(GL_DEPTH_TEST);
			glUseProgram(*debugShader);
			debugMatrix = glm::translate(camMatrix, entPtr->boundingBox.transform.position);
			glUniformMatrix4fv(CAMERA_MATRIX_ATTRIB_LOCATION, 1, GL_FALSE, glm::value_ptr(debugMatrix));
			glUniform3f(TEXT_COLOR_UNIFORM_LOCATION, entPtr->boundingBox.debugColor.r, entPtr->boundingBox.debugColor.g, entPtr->boundingBox.debugColor.b);
			glBindVertexArray(VAO);
			GLfloat vertices[6][3] = 
			{
				{ -entPtr->boundingBox.transform.scale.x, entPtr->boundingBox.transform.scale.y, 0},
				{ -entPtr->boundingBox.transform.scale.x, -entPtr->boundingBox.transform.scale.y, 0 },
				{ entPtr->boundingBox.transform.scale.x, -entPtr->boundingBox.transform.scale.y, 0 },

				{ -entPtr->boundingBox.transform.scale.x, entPtr->boundingBox.transform.scale.y, 0 },
				{ entPtr->boundingBox.transform.scale.x, -entPtr->boundingBox.transform.scale.y, 0 },
				{ entPtr->boundingBox.transform.scale.x, entPtr->boundingBox.transform.scale.y, 0 },
			};
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable(GL_DEPTH_TEST);
	}
	glBindVertexArray(0);
	glfwSwapInterval(1);
	glfwSwapBuffers(window);
	glfwPollEvents();
}/**/

void Renderer::SetRenderLayered(bool useLayeredRendering)
{
	this->useLayeredRendering = useLayeredRendering;
	if (useLayeredRendering)
	{
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND); glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	else
	{
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
	}
}

void Renderer::Update(Camera* camera)
{
	if (useLayeredRendering)
	{
		RenderLayered(camera);
	}
	/*else
	{
		RenderZBuffer(camera);
	}/**/
}
