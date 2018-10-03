#pragma once
#define GLEW_STATIC
#include <GL\glew.h>
#include <GL\GL.h>
#include <GLFW\glfw3.h>
#include <vector>
#include <fstream>

class ShaderLoader
{
	std::vector<GLuint*> shaderPrograms;
	std::string version;
	std::string preamble;

	static std::string ShaderStringFromFile(const char* filename)
	{
		std::ifstream fs(filename);
		if (!fs)
		{
			return "";
		}

		std::string s(
			std::istreambuf_iterator<char>{fs},
			std::istreambuf_iterator<char>{});

		return s;
	}

	void SetVersion(const char* filename)
	{
		this->version = version;
	}

	void SetPreamble(const char* preambleFilename)
	{
		preamble = ShaderStringFromFile(preambleFilename);
	}

	GLuint* AddVertFragProgram(std::string vertexShaderFilename, std::string fragmentShaderFilename)
	{
		return nullptr;
	}
};