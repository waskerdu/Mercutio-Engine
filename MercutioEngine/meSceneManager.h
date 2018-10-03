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
class SceneManager : public Entity
{
public:
	Entity* enemy;
	Editor* editor;
	Entity* monsterSpawn;
	Camera* camera;
	Entity* red;
	Barrier* barrier;
	Menu* mainMenu;
	Menu* pauseMenu;
	Menu* gameOverMenu;
	Menu* levelSelectMenu;
	Text* survivedTimeText;
	Text* enemiesKilledText;
	Material* armoredEnemyMatter;
	InputManager* inputManager;
	CharacterSelector* characterSelector;
	enum State
	{
		titleMenu,
		singleplayer,
		coop,
		running,
		levelSelect,
		lobby,
		gameEnd
	};
	State state = titleMenu;
	State lastState = lobby;
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
	double slowdownDuration = 0.3;
	double slowdown = 0.5;
	int enemiesKilled = 0;
	bool spawning = true;
	bool reincarnate = true;
	bool gameOver = true;
	float enemyDistance = 800.0f;
	int waveMaxSize = 10;
	int waveMinSize = 2;
	int waveSize = 2;
	double lobbyLaunchRadius = 200;
	double throwerProb = 0.5;
	bool lastNeedsWave = false;
	bool canOptInOut = false;
	std::string currentLevel = "";
	bool firstTime = true;

	//void EnemyWave(int enemies);
	//void EnemyWave();
	//void LaunchMatch();
	void SceneUpdate();
	void AddActor(int numActors);
	//void CreateLobby();
	//void PlaceBarriers();

	SceneManager();
	~SceneManager();
	void Update();
	//void Awake();
	void Reset();
};

