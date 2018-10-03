#pragma once
#include "meMesh.h"
#include <map>
#include <SFML\Audio.hpp>
#include "meMaterial.h"
#include "shaderset.h"
#include "meCharacter.h"
#include <iostream>
#include <ft2build.h>
#include FT_FREETYPE_H 

enum WindowMode
{
	windowed,
	fullscreen,
	borderlessFullscreen
};

class AssetManager
{
	//Asset Manager manages all the data that entities in the World object can use
	std::string textureManifestFilepath = "assets/textures/texture_manifest.txt";
public:

	GLFWwindow* window;
	int windowWidth = 800;
	int windowHeight = 600;
	int viewWidth = 800;
	int viewHeight = 600;
	WindowMode windowMode = borderlessFullscreen;
	//windowMode = windowed;
	int monitor = 0;

	ShaderSet shaderSet;
	GLuint* shader;

	FT_Library ft;

	std::map<std::string, int> textureRef;
	std::map<std::string, int> meshRef;
	std::map<std::string, int> soundRef;
	std::map<std::string, std::string> musicRef;
	std::map<std::string, int> fontRef;
	std::map<std::string, GLuint*> shaders;

	std::vector<Mesh*> meshes;
	std::vector<GLuint> textures;
	std::vector<Material*> materials;
	std::vector<sf::SoundBuffer*> soundBuffers;
	std::vector<std::map<GLchar, Character>*> fonts;
private:

	void MeshInit();//initalizes built in meshes

public:

	GLuint* GetShader(std::string alias);

	void LoadShader(std::string alias, std::string vertShader, std::string fragShader);

	void CreateFont(std::string alias, std::string filename, float width, float height);

	void LoadTextures();

	std::map<GLchar, Character>* GetFont(std::string alias);

	void FreeFonts();

	sf::SoundBuffer* GetSoundBuffer(std::string alias);

	bool LoadSoundBuffer(std::string filename, std::string alias);

	Mesh* GetMesh(std::string alias)
	{
		if (meshRef.count(alias) == 0) { std::cout << alias << " is an invalid mesh alias.\n"; }
		return meshes[meshRef[alias]];
	}

	void CreateMesh(std::string alias, std::string base, glm::mat4 transform);

	Material* GetMaterial(std::string alias)
	{
		if (textureRef.count(alias) == 0) { std::cout << alias << " is an invalid texture alias.\n"; }
		return materials[textureRef[alias]];
	}

	bool CreateMaterial(std::string alias, std::string textureFilename, std::string shaderAlias);

	void SetSize();

	void FreeMaterials();

	void FreeSoundBuffers();

	void FreeMemory()
	{
		FreeMaterials();
		FreeSoundBuffers();
		FT_Done_FreeType(ft);
	}

	AssetManager();

	~AssetManager()
	{
		FreeMemory();
	}
};