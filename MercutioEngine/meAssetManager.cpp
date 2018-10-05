#include "stdafx.h"
#include "meAssetManager.h"
#include "meParser.h"
#include <fstream>

void AssetManager::LoadTextures()
{
	std::fstream file;
	std::string line;
	std::vector<std::string> parsedLine;

	file.open(textureManifestFilepath.c_str());
	if (!file.is_open())
	{
		std::cout << "File " << textureManifestFilepath << " failed to open.\n";
		return;
	}

	while (std::getline(file, line))
	{
		Parser(line, parsedLine);
		if (parsedLine.size() != 3) { continue; }
		if (parsedLine[0][0] == '/') { continue; }
		CreateMaterial(parsedLine[0], parsedLine[1], parsedLine[2]);
	}
}

void AssetManager::MeshInit()
{
	meshes = std::vector<Mesh*>();
	FreeMemory();
	std::vector<float> verts
	{
		//positions             //colors			    //texture coords
		50.0f,  50.0f, 0.0f,   1.0f, 0.0f, 0.0f,		1.0f, 1.0f,
		50.0f, -50.0f, 0.0f,   0.0f, 1.0f, 0.0f,		1.0f, 0.0f,
		-50.0f, -50.0f, 0.0f,   0.0f, 0.0f, 1.0f,		0.0f, 0.0f,
		-50.0f,  50.0f, 0.0f,   1.0f, 1.0f, 0.0f,		0.0f, 1.0f
	};
	std::vector<float> playerVertices
	{
		//positions             //colors			    //texture coords
		50.0f,  75.0f, 0.0f,   1.0f, 0.0f, 0.0f,		1.0f, 1.0f,
		50.0f, -75.0f, 0.0f,   0.0f, 1.0f, 0.0f,		1.0f, 0.0f,
		-50.0f, -75.0f, 0.0f,   0.0f, 0.0f, 1.0f,		0.0f, 0.0f,
		-50.0f,  75.0f, 0.0f,   1.0f, 1.0f, 0.0f,		0.0f, 1.0f
	};

	std::vector<float> wokVertices
	{
		//positions             //colors			    //texture coords
		75.0f,  50.0f, 0.0f,   1.0f, 0.0f, 0.0f,		1.0f, 1.0f,
		75.0f, -50.0f, 0.0f,   0.0f, 1.0f, 0.0f,		1.0f, 0.0f,
		-75.0f, -50.0f, 0.0f,   0.0f, 0.0f, 1.0f,		0.0f, 0.0f,
		-75.0f,  50.0f, 0.0f,   1.0f, 1.0f, 0.0f,		0.0f, 1.0f
	};
	std::vector<unsigned int> indices{
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};
	std::vector<float> tiling
	{
		//positions             //colors			    //texture coords
		100000.0f,  100000.0f, 0.0f,   1.0f, 0.0f, 0.0f,		1000.0f, 1000.0f,
		100000.0f, -100000.0f, 0.0f,   0.0f, 1.0f, 0.0f,		1000.0f, -1000.0f,
		-100000.0f, -100000.0f, 0.0f,   0.0f, 0.0f, 1.0f,		-1000.0f, -1000.0f,
		-100000.0f,  100000.0f, 0.0f,   1.0f, 1.0f, 0.0f,		-1000.0f, 1000.0f
	};
	meshes.push_back(new Mesh(verts, indices));
	meshRef["quad"] = (int)meshes.size() - 1;
	meshes.push_back(new Mesh(playerVertices, indices));
	meshRef["ninja"] = (int)meshes.size() - 1;
	meshes.push_back(new Mesh(wokVertices, indices));
	meshRef["wok"] = (int)meshes.size() - 1;
	meshes.push_back(new Mesh(tiling, indices));
	meshRef["terrain"] = (int)meshes.size() - 1;
}

void AssetManager::CreateMesh(std::string alias, std::string base, glm::mat4 transform)
{
	Mesh* meshPtr = new Mesh(GetMesh(base)->vertices, GetMesh(base)->indices);
	for (uint32_t i = 0; i < meshPtr->vertices.size(); i+=8)
	{
		glm::vec4 tempVec(meshPtr->vertices.at(i), meshPtr->vertices.at(i+1), meshPtr->vertices.at(i+2), 1);
		tempVec = transform * tempVec;
		meshPtr->vertices.at(i) = tempVec.x;
		meshPtr->vertices.at(i+1) = tempVec.y;
		meshPtr->vertices.at(i+2) = tempVec.z;
	}
	meshPtr->Init();
	meshes.push_back(meshPtr);
	meshRef[alias] = (int)meshes.size() - 1;
	//meshRef.insert(std::pair<std::string, int>(alias, meshes.size() - 1));
	//std::cout << meshRef.count(alias) << "\n";
}

sf::SoundBuffer* AssetManager::GetSoundBuffer(std::string alias)
{
	if (soundRef.count(alias) == 0) { std::cout << alias << " is an invalid sound buffer alias.\n"; }
	return soundBuffers[soundRef[alias]];
}

bool AssetManager::LoadSoundBuffer(std::string filename, std::string alias)
{
	soundBuffers.push_back(new sf::SoundBuffer);
	if (!soundBuffers.back()->loadFromFile(filename))
	{
		std::cout << filename << " not found.\n";
		return false;
	}
	else
	{
		soundRef[alias] = (int)soundBuffers.size() - 1;
		return true;
	}
}

char MultiplyAlpha(char a, char b)
{
	float af = (float)a;
	float bf = (float)b;
	af /= 255.0f;
	bf /= 255.0f;
	bf = 1.0f - bf;
	af *= bf;
	af *= 255.0f;
	return (char)af;
}

bool AssetManager::CreateMaterial(std::string alias, std::string textureFilename, std::string shaderAlias)
{
	textures.push_back(0);
	textureRef[alias] = (int)textures.size() - 1;
	unsigned char* textureData;
	glGenTextures(1, &textures.back());
	glBindTexture(GL_TEXTURE_2D, textures.back());
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	textureData = stbi_load(textureFilename.c_str(), &width, &height, &nrChannels, 0);
	if (textureData)
	{
		/*for (int i = 0; i < width * 4; i+=4)
		{
			for (int f = 0; f < height; f++)
			{
				if (i == 0 && f == 0)
				{
					std::cout << (int)textureData[3]<<" ";
				}
				textureData[i + f * width * 4] = MultiplyAlpha(textureData[i + f * width * 4], textureData[i + 3 + f * width * 4]);
				textureData[i + 1 + f * width * 4] = MultiplyAlpha(textureData[i + 1 + f * width * 4], textureData[i + 3 + f * width * 4]);
				textureData[i + 2 + f * width * 4] = MultiplyAlpha(textureData[i + 2 + f * width * 4], textureData[i + 3 + f * width * 4]);
			}
		}/**/
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		//std::cout << "failed to load texture\n";
		std::cout << textureFilename << " failed to load.\n";
		return false;
	}
	stbi_image_free(textureData);
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	materials.push_back(new Material(textures.back(), GetShader(shaderAlias)));
	return true;
}

void AssetManager::SetSize()
{

	if (windowMode == fullscreen || windowMode == borderlessFullscreen)
	{
		int numMonitors;
		GLFWmonitor** monitors = glfwGetMonitors(&numMonitors);

		if (monitor > -1 && monitor < numMonitors)
		{
			const GLFWvidmode* mode = glfwGetVideoMode(monitors[monitor]);
			windowHeight = mode->height;
			windowWidth = mode->width;
			glfwWindowHint(GLFW_RED_BITS, mode->redBits);
			glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
			glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
			glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);
			glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
			glfwSetWindowMonitor(window, monitors[monitor], 0, 0, mode->width, mode->height, mode->refreshRate);
			glViewport(0, 0, windowWidth, windowHeight);
			std::cout << mode->width << " " << mode->height << "\n";
			return;
		}
	}
	//glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
	glfwSetWindowSize(window, windowWidth, windowHeight);
	glViewport(0, 0, viewWidth, viewHeight);
}

AssetManager::AssetManager()
{
	MeshInit();
	window = glfwCreateWindow(windowWidth, windowHeight, "WOK", NULL, NULL);
	SetSize();
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(window);
	glViewport(0, 0, windowWidth, windowHeight);
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
	}
	fprintf(stdout, "OpenGl Version: %s\n", glGetString(GL_VERSION));
	fprintf(stdout, "Vendor: %s\n", glGetString(GL_VENDOR));
	fprintf(stdout, "Renderer: %s\n", glGetString(GL_RENDERER));

	shaderSet.SetVersion("430");
	shaderSet.SetPreambleFile("assets/shaders/preamble.glsl");

	if (FT_Init_FreeType(&ft))
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

	//MeshInit();
	for (size_t i = 0; i < meshes.size(); i++)
	{
		meshes[i]->Init();
	}
}

void AssetManager::LoadShader(std::string alias, std::string vertShader, std::string fragShader)
{
	shader = shaderSet.AddProgramFromExts({ vertShader, fragShader });
	shaders[alias] = shader;
	shaderSet.UpdatePrograms();
}

GLuint* AssetManager::GetShader(std::string alias)
{
	if (shaders.count(alias) == 0) { std::cout << alias << " is not a valid shader name.\n"; }
	return shaders[alias];
}

void AssetManager::FreeMaterials()
{
	for (uint32_t i = 0; i < materials.size(); i++)
	{
		delete materials[i];
	}
	materials.clear();
}

void AssetManager::FreeSoundBuffers()
{
	for (uint32_t i = 0; i < soundBuffers.size(); i++)
	{
		delete soundBuffers[i];
	}
	soundBuffers.clear();
}

void AssetManager::CreateFont(std::string alias, std::string filename, float width, float height)
{
	fonts.push_back(new std::map<GLchar, Character>);
	fontRef[alias] = (int)fonts.size() - 1;
	FT_Face face;
	if (FT_New_Face(ft, filename.c_str(), 0, &face))
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

	FT_Set_Pixel_Sizes(face, (FT_UInt)width, (FT_UInt)height);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

	for (GLubyte c = 0; c < 128; c++)
	{
		// Load character glyph 
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
			continue;
		}
		// Generate texture
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer
		);
		// Set texture options
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		// Now store character for later use
		Character character = {
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			(GLuint)face->glyph->advance.x
		};
		fonts.back()->insert(std::pair<GLchar, Character>(c, character));
	}
	FT_Done_Face(face);
}

void AssetManager::FreeFonts()
{
	for (uint32_t i = 0; i < fonts.size(); i++)
	{
		delete fonts[i];
	}
	fonts.clear();
}

std::map<GLchar, Character>* AssetManager::GetFont(std::string alias)
{
	if (fontRef.count(alias) == 0) { std::cout << alias << " is not a valid font name.\n"; }
	return fonts.at(fontRef[alias]);
}