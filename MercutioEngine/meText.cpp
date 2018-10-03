#include "stdafx.h"
#include "meText.h"
#include "assets\shaders\preamble.glsl"
#include <string>

Entity* Text::Copy()
{
	//copy creates a new object based on another object and returns it. sub classes will write their own version
	Text* copy = new Text(*this);
	DeepCopy(this, copy);
	return copy;
}

Text::Text()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	//glEnableVertexAttribArray(POSITION_ATTRIB_LOCATION);
	glVertexAttribPointer(POSITION_ATTRIB_LOCATION, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	layer = Entity::ui;
}

Text::~Text()
{

}

void Text::Confirm()
{
	messagesSent++;
}

void Text::Inc()
{
	iter++;
	Bump();
}

void Text::Dec()
{
	iter--;
	Bump();
}

void Text::Bump()
{
	if (iter < minVal)
	{
		if (loop) { iter = maxVal;}
		else { iter = minVal; }
	}
	else if (iter > maxVal)
	{
		if (loop) { iter = minVal; }
		else { iter = maxVal; }
	}
	if (useIter)
	{
		if (iter > -1 && iter < (signed int)inserts.size() - 1)
		{
			text = startText + inserts[iter] + endText;
		}
		else
		{
			text = startText + std::to_string(iter) + endText;
		}
	}
	
}

void Text::Render(RenderData* data)
{
	glUseProgram(*shader);
	glUniformMatrix4fv(CAMERA_MATRIX_ATTRIB_LOCATION, 1, GL_FALSE, glm::value_ptr(data->viewMatrix));
	glUniform3f(TEXT_COLOR_UNIFORM_LOCATION, color.x, color.y, color.z);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(VAO);
	//std::cout << transform.position.x - parent->transform.position.x << "\n";
	GLfloat x, y, scale;
	//x = transform.position.x;
	//y = transform.position.y;
	x = 0;
	y = 0;
	scale = 1;
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = font->at(*c);
		GLfloat xpos = x + ch.Bearing.x * scale;
		GLfloat ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

		GLfloat w = ch.Size.x * scale;
		GLfloat h = ch.Size.y * scale;
		// Update VBO for each character
		GLfloat vertices[6][4] = {
			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos,     ypos,       0.0, 1.0 },
			{ xpos + w, ypos,       1.0, 1.0 },

			{ xpos,     ypos + h,   0.0, 0.0 },
			{ xpos + w, ypos,       1.0, 1.0 },
			{ xpos + w, ypos + h,   1.0, 0.0 }
		};
		// Render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.textureID);
		// Update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// Render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
	}
	width = x - transform.position.x;
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}