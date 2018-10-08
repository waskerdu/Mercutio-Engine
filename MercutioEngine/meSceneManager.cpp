#include "stdafx.h"
#include "meSceneManager.h"
#include "meEnemy.h"
#include "meEnemyAggro.h"
#include "meEngineInterface.h"
#include "wokLevelEnd.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::SendMessage(std::string message, Entity* ent)
{
	//
	std::cout << message << "\n";
	if (message == "singleplayer") 
	{
		menuManager->SelectMenu("levelSelect");
	}
	else if (message == "coop") 
	{
		menuManager->SelectMenu("levelSelect");
		canOptInOut = true;
	}
	else if (message == "options") 
	{
		menuManager->SelectMenu("options");
	}
	else if (message == "exit") 
	{
		EngineInterface::Quit(this);
	}
	else if (message == "resume") 
	{
		EngineInterface::Pause(this, false);
		menuManager->SetAwake(false);
	}
	else if (message == "restart") 
	{
		state = running;
		lastState = none;
		currentLevel = lobbyFilepath;
		EngineInterface::Reset(this);
		EngineInterface::Pause(this, false);
		menuManager->SetAwake(false);
	}
	else if (message == "back")
	{
		menuManager->SelectPreviousMenu();
	}
	else if (message == "checkpoint")
	{
		currentLevel = checkpointLevel;
		state = running;
		lastState = none;
		menuManager->SetAwake(false);
		EngineInterface::Reset(this);
		EngineInterface::Pause(this, false);
	}
	else if (message == "mainMenu") 
	{
		state = titleMenu;
		lastState = none;
		EngineInterface::Reset(this);
	}
	else if (message == "graphics")
	{
		menuManager->SelectMenu("graphics");
	}
	else if (message == "audio")
	{
		menuManager->SelectMenu("audio");
	}
	else if (message == "resolution")
	{
		menuManager->SelectMenu("resolution");
	}
	else if (message[0] == '!')//is a level file
	{
		message.erase(0, 1);
		savedLevel = message;
		state = running;
		lastState = none;
		currentLevel = lobbyFilepath;
		checkpointLevel = currentLevel;
		menuManager->SetAwake(false);
	}
	else if (message == "options_confirm")
	{
		EngineInterface::OptionsConfirm(this);
	}
	else if (message == "window_mode_inc" || message == "window_mode_dec")
	{
		if (EngineInterface::GetWindowMode(this) == MonitorMode::borderlessFullscreen)
		{
			EngineInterface::SetMode(this, MonitorMode::windowed);
			dynamic_cast<Text*>(ent)->SetText("WINDOW MODE: WINDOWED");
			std::cout << "windowed\n";
		}
		else
		{
			EngineInterface::SetMode(this, MonitorMode::borderlessFullscreen);
			dynamic_cast<Text*>(ent)->SetText("WINDOW MODE: BORDERLESS FULLSCREEN");
		}
	}
	else if (message == "vsync")
	{
		if (EngineInterface::GetVsync(this) == 1)
		{
			EngineInterface::SetVsync(this, 0);
			dynamic_cast<Text*>(ent)->SetText("V-SYNC: OFF");
		}
		else
		{
			EngineInterface::SetVsync(this, 1);
			dynamic_cast<Text*>(ent)->SetText("V-SYNC: ON");
		}
	}
}

void SceneManager::AddActor(int numActors)
{
	for (int i = 0; i < numActors; i++)
	{
		Actor* newRed = dynamic_cast<Actor*>((red->Copy()));
		initQueue.push_back(newRed);
		camera->targets.push_back(newRed);
		spawnedActors.push_back(newRed);
		newRed->SetCharacter(Actor::red);
	}
}

void SceneManager::Reset()
{
	spawnedEnemies.clear();
	spawnWarnings.clear();
}

void SceneManager::Update() 
{
	if (inputManager->aggregateController->GetButton("resize"))
	{
		EngineInterface::SetMode(this, MonitorMode::windowed);
		EngineInterface::OptionsConfirm(this);
	}
	if (inputManager->aggregateController->GetButton("resize2"))
	{
		EngineInterface::SetMode(this, MonitorMode::borderlessFullscreen);
		EngineInterface::OptionsConfirm(this);
	}
	if (firstTime)
	{
		AddActor(6);
		spawnedActors[0]->controller = inputManager->controllers[0];
		spawnedActors[1]->controller = inputManager->controllers[1];
		spawnedActors[2]->controller = inputManager->controllers[2];
		spawnedActors[3]->controller = inputManager->controllers[3];
		spawnedActors[4]->controller = inputManager->mkController;
		spawnedActors[5]->controller = inputManager->aggregateController;
		for (uint32_t i = 0; i < spawnedActors.size(); i++)
		{
			spawnedActors[i]->SetAwake(false);
			spawnedActors[i]->SetCharacter(Actor::none);
			spawnedActors[i]->SetDeleteStatus(true);
		}
		firstTime = false;
	}
	std::vector<Entity*> spawned;
	editor->GetEnemies(&spawned);
	for (uint32_t i = 0; i < spawned.size(); i++)
	{
		spawnedEnemies.push_back(spawned.at(i));
	}

	bool newState = state != lastState;
	//if (newState && state != running) { survivedTimeText->SetAwake(false); }
	lastState = state;

	if (inputManager->aggregateController->GetButton("menuCancel"))
	{
		menuManager->SelectPreviousMenu();
	}

	switch (state)
	{
	case SceneManager::titleMenu:
		if (newState)
		{
			//make title menu visible
			menuManager->SelectMenu("main");
			for (uint32_t i = 0; i < spawnedActors.size(); i++)
			{
				spawnedActors[i]->SetAwake(false);
			}
			canOptInOut = false;
		}
		break;
	case SceneManager::running:
		if (newState)
		{
			if (currentLevel == "saved") 
			{ 
				currentLevel = savedLevel;
			}
			if (currentLevel == "checkpoint") { currentLevel = checkpointLevel; }
			editor->LoadLevel(currentLevel);
			if (currentLevel == lobbyFilepath)
			{
				if (canOptInOut == false)
				{
					spawnedActors[5]->SetAwake(true);
					spawnedActors[5]->SetCharacter(Actor::Character::none);
				}
				else
				{
					EngineInterface::Pause(this, false);
				}
			}
			else
			{
				canOptInOut = false;
			}
			for (uint32_t i = 0; i < spawnedActors.size(); i++)
			{
				editor->GetStartPos(&spawnedActors[i]->transform.position);
			}
		}
		//handle pause menu
		if (inputManager->aggregateController->GetButton("togglePause"))
		{
			if (EngineInterface::IsPaused(this))
			{
				EngineInterface::Pause(this, false);
				menuManager->SetAwake(false);
			}
			else
			{
				EngineInterface::Pause(this, true);
				menuManager->SetAwake(true);
				menuManager->SelectMenu("pause");
			}
		}
		if (canOptInOut)
		{
			for (uint32_t i = 0; i < spawnedActors.size() - 1; i++)
			{
				if (spawnedActors[i]->isAwake() && spawnedActors[i]->controller->GetButton("menuCancel")) { spawnedActors[i]->SetAwake(false); }
				if (spawnedActors[i]->isAwake() == false && spawnedActors[i]->controller->GetButton("menuConfirm")) 
				{ 
					spawnedActors[i]->SetAwake(true); 
					spawnedActors[i]->SetCharacter(Actor::Character::none);
				}
			}
		}
		SceneUpdate();
		break;
	case SceneManager::gameEnd:
		if (newState)
		{
			//show end game stuff
			SetDeltaTimeCo(0);
			int timeInt = (int)(timeSurvived*precision);
			if (survivedTimeText->isAwake() == false)
			{
				survivedTimeText->SetAwake(true);
				//enemiesKilledText->SetAwake(true);
				survivedTimeText->text = survivedTimeString + std::to_string(timeInt / (int)precision) + " seconds";
			}
			
			//enemiesKilledText->text = enemiesKilledString + std::to_string(enemiesKilled);
		}
		//manage endgame menu
		break;
	default:
		break;
	}
}

void SceneManager::SceneUpdate()
{
	bool needsWave = true;
	Enemy* currentEnemy;
	LevelEnd* levelEnd;

	for (uint32_t i = 0; i < spawnedEnemies.size(); i++)
	{
		currentEnemy = dynamic_cast<Enemy*>(spawnedEnemies[i]);
		if (currentEnemy->alive) { needsWave = false; }
	}
	
	if (needsWave)
	{
		if (editor->Wave() == false) 
		{ 
			if (editor->levelEnds.size() == 0)
			{
				SetDeltaTimeCo(0);
				int timeInt = (int)(timeSurvived*precision);
				if (survivedTimeText->isAwake() == false)
				{
					survivedTimeText->SetAwake(true);
					survivedTimeText->text = survivedTimeString + std::to_string(timeInt / (int)precision) + " seconds";
				}
			}
			for (uint32_t i = 0; i < editor->levelEnds.size(); i++)
			{
				levelEnd = dynamic_cast<LevelEnd*>(editor->levelEnds[i]);
				levelEnd->locked = false;
			}
		}
	}

	bool gameOver = true;
	if (canOptInOut) { gameOver = false; }
	for (uint32_t i = 0; i < spawnedActors.size(); i++)
	{
		if (spawnedActors[i]->alive && spawnedActors[i]->isAwake()) { gameOver = false; }
	}
	if (gameOver == false) { timeSurvived += deltaTime; }
	else
	{
		SetDeltaTimeCo(0);
		int timeInt = (int)(timeSurvived*precision);
		if (survivedTimeText->isAwake() == false)
		{
			survivedTimeText->SetAwake(true);
			//enemiesKilledText->SetAwake(true);
			//survivedTimeText->text = survivedTimeString + std::to_string(timeInt / (int)precision) + " seconds";
			survivedTimeText->text = survivedTimeString + std::to_string(timeInt / (int)precision) + " seconds";
		}
	}
	bool load = true;
	bool openLevel = false;
	bool oneAlive = false;
	for (uint32_t i = 0; i < editor->levelEnds.size(); i++)
	{
		levelEnd = dynamic_cast<LevelEnd*>(editor->levelEnds[i]);
		load = true;
		openLevel = !levelEnd->locked;
		for (uint32_t f = 0; f < spawnedActors.size(); f++)
		{
			if (spawnedActors[f]->isAwake() && spawnedActors[f]->alive)
			{
				if (glm::length(levelEnd->transform.position - spawnedActors[f]->transform.position) < levelEnd->radius) {}
				else { load = false;}
				if (spawnedActors[f]->character == Actor::none) { load = false; openLevel = false; }
				oneAlive = true;
			}
		}
		if (oneAlive && openLevel && levelEnd->IsOpen() == false) { levelEnd->SetOpen(true); }
		else if (openLevel == false && levelEnd->IsOpen()) { levelEnd->SetOpen(false); }
		if (load&&oneAlive&&openLevel)
		{
			//std::cout << levelEnd->nextLevel << " loaded.\n";
			canOptInOut = false;
			currentLevel = levelEnd->nextLevel;
			EngineInterface::Reset(this);
			lastState = none;
			//std::cout << state << " " << lastState << "\n";
			break;
		}
	}
}/**/