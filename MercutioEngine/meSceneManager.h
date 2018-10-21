#pragma once
#include "meEntity.h"
#include "meCamera.h"
#include "meBarrier.h"
#include "meActor.h"
#include "meText.h"
#include "meMenu.h"
#include "meInput.h"
#include "meCharacterSelector.h"
#include "wokEditor.h"
#include "meMenuManager.h"
class SceneManager : public Entity
{
public:
	Entity* enemy;
	Editor* editor;
	Entity* monsterSpawn;
	Camera* camera;
	Entity* red;
	Barrier* barrier;
	Entity* logo;
	/*Menu* mainMenu;
	Menu* pauseMenu;
	Menu* gameOverMenu;
	Menu* levelSelectMenu;/**/
	Text* survivedTimeText;
	Text* enemiesKilledText;
	Material* armoredEnemyMatter;
	InputManager* inputManager;
	CharacterSelector* characterSelector;
	MenuManager* menuManager;
	int numVideoModes;
	const GLFWvidmode* modes;
	//const GLFWvidmode* videoMode;
	bool unsavedChanges = false;
	int currentMonitorIndex = 0;
	enum State
	{
		titleMenu,
		singleplayer,
		coop,
		running,
		levelSelect,
		lobby,
		gameEnd,
		none
	};
	State state = titleMenu;
	State lastState = none;
	State lastActiveState = singleplayer;
	float arenaRadius = 1500;
	std::vector<Actor::Character> heros = {Actor::ted, Actor::key, Actor::tan };
	std::vector<Entity*> spawnedEnemies;
	std::vector<Actor*> spawnedActors;
	std::vector<Entity*> spawnWarnings;
	std::string survivedTimeString = "TIME: ";
	std::string enemiesKilledString = "ENEMIES KILLED: ";
	double timeSurvived = 0;
	double precision = 100;
	bool spawning = true;
	bool canOptInOut = false;
	std::string currentLevel = "";
	std::string savedLevel = "";
	std::string checkpointLevel = "";
	std::string lobbyFilepath = "assets/levels/official/lobby.txt";
	bool firstTime = true;
	void SceneUpdate();
	void AddActor(int numActors);

	SceneManager();
	~SceneManager();
	void Update();
	void Reset();
	void SendMessage(std::string message, Entity* ent);
	void OptionsUpdate();
};

