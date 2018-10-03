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
	if (newState && state != running) { survivedTimeText->SetAwake(false); }
	lastState = state;

	switch (state)
	{
	case SceneManager::titleMenu:
		if (newState)
		{
			//make title menu visible
			mainMenu->SetAwake(true);
			for (uint32_t i = 0; i < spawnedActors.size(); i++)
			{
				spawnedActors[i]->SetAwake(false);
			}
		}
		//manage menu
		if (mainMenu->FindMessage("exit", Menu::confirm))
		{
			EngineInterface::Quit(this);
		}
		else if (mainMenu->FindMessage("singleplayer", Menu::confirm))
		{
			mainMenu->SetAwake(false);
			state = levelSelect;
		}
		else if (mainMenu->FindMessage("coop", Menu::confirm))
		{
			mainMenu->SetAwake(false);
			canOptInOut = true;
			state = levelSelect;
		}
		break;
	case SceneManager::singleplayer://not used
		break;
	case SceneManager::coop://not used
		break;
	case SceneManager::levelSelect:
		if (newState)
		{
			levelSelectMenu->SetAwake(true);
		}
		if (levelSelectMenu->FindMessage("arena", Menu::confirm))
		{
			currentLevel = "assets/levels/official/lobby.txt";
			levelSelectMenu->SetAwake(false);
			if (canOptInOut == false) 
			{ 
				spawnedActors[5]->SetAwake(true);
				spawnedActors[5]->SetCharacter(Actor::Character::none);
			}
			state = running;
		}
		if (levelSelectMenu->FindMessage("back", Menu::confirm) || inputManager->aggregateController->GetButton("menuCancel"))
		{
			state = titleMenu;
			levelSelectMenu->SetAwake(false);
			EngineInterface::Reset(this);
		}
		break;
	case SceneManager::running:
		if (newState)
		{
			editor->LoadLevel(currentLevel);
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
				pauseMenu->SetAwake(false);
			}
			else
			{
				EngineInterface::Pause(this, true);
				pauseMenu->SetAwake(true);
			}
		}
		if (pauseMenu->isAwake())
		{
			if (pauseMenu->FindMessage("resume", Menu::confirm) || inputManager->aggregateController->GetButton("menuCancel"))
			{
				EngineInterface::Pause(this, false);
				pauseMenu->SetAwake(false);
				pauseMenu->Clear();
				return;
			}
			if (pauseMenu->FindMessage("reset", Menu::confirm))
			{
				EngineInterface::Reset(this);
				EngineInterface::Pause(this, false);
				pauseMenu->SetAwake(false);
				for (uint32_t i = 0; i < spawnedActors.size(); i++)
				{
					if (spawnedActors[i]->isAwake()) { spawnedActors[i]->SetCharacter(spawnedActors[i]->character); }//sets dead actors to full health
				}
				//load current level
				editor->LoadLevel(currentLevel);
			}
			if (pauseMenu->FindMessage("exit", Menu::confirm))
			{
				EngineInterface::Quit(this);
			}
			else if (pauseMenu->FindMessage("mainMenu", Menu::confirm))
			{
				state = titleMenu;
				EngineInterface::Reset(this);
				EngineInterface::Pause(this, false);
				pauseMenu->SetAwake(false);
				for (uint32_t i = 0; i < spawnedActors.size(); i++)
				{
					spawnedActors[i]->SetCharacter(Actor::none);
				}
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
	case SceneManager::lobby://not used
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
			//std::cout << "you win!\n"; 
			if (editor->levelEnds.size() == 0)
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
				/*SetDeltaTimeCo(0);
				int timeInt = (int)(timeSurvived*precision);
				survivedTimeText->SetAwake(true);
				//enemiesKilledText->SetAwake(true);
				survivedTimeText->text = survivedTimeString + std::to_string(timeInt / (int)precision) + " seconds";*/
				//enemiesKilledText->text = enemiesKilledString + std::to_string(enemiesKilled);/**/
				//state = gameEnd;
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
			std::cout << levelEnd->nextLevel << " loaded.\n";
			canOptInOut = false;
			currentLevel = levelEnd->nextLevel;
			EngineInterface::Reset(this);
			lastState = titleMenu;
			break;
		}
	}
}/**/