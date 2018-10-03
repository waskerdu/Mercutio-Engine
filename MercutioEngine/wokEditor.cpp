#include "stdafx.h"
#include <fstream>
#include <map>
#include "wokEditor.h"
#include "meParser.h"
#include "meBarrier.h"
#include "wokEnemySpawner.h"
#include "meCharacterSelector.h"
#include "wokLevelEnd.h"
#include "wokNavNode.h"
#include "wokPressurePlate.h"
#include "wokDoor.h"

Editor::Editor()
{
	entityTypes["#PlayerSpawner"] = _playerSpawner;
	entityTypes["#EnemySpawner"] = _enemySpawner;
	entityTypes["#PlayerSpawner"] = _playerSpawner;
	entityTypes["#Barrier"] = _barrier;
	entityTypes["#NavNode"] = _navNode;
	entityTypes["#CharacterSelector"] = _characterSelector;
	entityTypes["#LevelEnd"] = _levelEnd;
	entityTypes["#PressurePlate"] = _pressurePlate;
	entityTypes["#Door"] = _door;

	argumentTypes["Position"] = _position;
	argumentTypes["Scale"] = _scale;
	argumentTypes["Radius"] = _radius;
	argumentTypes["WaveSize"] = _waveSize;
	argumentTypes["WaveIncriment"] = _waveIncriment;
	argumentTypes["NumberOfWaves"] = _numberOfWaves;
	argumentTypes["Locked"] = _locked;
	argumentTypes["Character"] = _character;
}


Editor::~Editor()
{
}

void Editor::Update()
{
	//std::cout << doors.size() << "\n";
}

bool Editor::NeedsWave()
{
	EnemySpawner* spawner;
	bool needsWave = true;
	for (uint32_t i = 0; i < enemySpawners.size(); i++)
	{
		spawner = dynamic_cast<EnemySpawner*>(enemySpawners[i]);
		for (uint32_t f = 0; f < spawner->spawnedEnemies.size(); f++)
		{
			if (spawner->spawnedEnemies[f]->isAwake())
			{
				needsWave = false;
			}
		}
	}
	return needsWave;
}

void Editor::GetStartPos(glm::vec3* pos)
{
	pos->x = std::min(pos->x, levelStart->transform.position.x - levelStart->boundingBox.transform.scale.x);
	pos->x = std::max(pos->x, levelStart->transform.position.x + levelStart->boundingBox.transform.scale.x);
	pos->y = std::min(pos->y, levelStart->transform.position.y - levelStart->boundingBox.transform.scale.y);
	pos->y = std::max(pos->y, levelStart->transform.position.y + levelStart->boundingBox.transform.scale.y);
}

bool Editor::Wave()
{
	//dynamic_cast<EnemySpawner*>(enemySpawners[0])->Wave();
	EnemySpawner* spawner;
	bool canStillWave = false;
	for (uint32_t i = 0; i < enemySpawners.size(); i++)
	{
		//dynamic_cast<EnemySpawner*>(enemySpawners[i])->Wave();
		spawner = dynamic_cast<EnemySpawner*>(enemySpawners[i]);
		if (spawner->numberOfWaves != 0) { canStillWave = true; }
		spawner->Wave();
	}
	return canStillWave;
}

void Editor::GetEnemies(std::vector<Entity*>* vec)
{
	EnemySpawner* spawner;
	for (uint32_t i = 0; i < enemySpawners.size(); i++)
	{
		spawner = dynamic_cast<EnemySpawner*>(enemySpawners[i]);
		for (uint32_t f = 0; f < spawner->spawnedEnemies.size(); f++)
		{
			vec->push_back(spawner->spawnedEnemies[f]);
		}
		spawner->spawnedEnemies.clear();
	}
}

void Editor::Reset()
{
	barriers.clear();
	enemySpawners.clear();
	levelEnds.clear();
	characterSelectors.clear();
}

glm::vec3 Editor::GetVec3(std::vector<std::string> line, int lineStart)
{
	return glm::vec3(std::stoi(line[lineStart]), std::stoi(line[lineStart + 1]), std::stoi(line[lineStart + 2]));
}

void Editor::SetEntPosition(Entity* ent, std::vector<std::string> line, int lineStart)
{
	ent->transform.position = glm::vec3(std::stoi(line[lineStart]), std::stoi(line[lineStart + 1]), std::stoi(line[lineStart + 2]));
}

void Editor::SetEntPosition(Entity* ent, std::vector<std::string> line, int &lineStart)
{
	ent->transform.position = glm::vec3(std::stoi(line[lineStart]), std::stoi(line[lineStart + 1]), std::stoi(line[lineStart + 2]));
	lineStart += 3;
}

void Editor::SetEntScale(Entity* ent, std::vector<std::string> line, int &lineStart)
{
	ent->transform.scale *= glm::vec3(std::stoi(line[lineStart]), std::stoi(line[lineStart + 1]), std::stoi(line[lineStart + 2]));
	lineStart += 3;
}

void Editor::SetEntScale(Transform* trans, std::vector<std::string> line, int lineStart)
{
	trans->scale *= glm::vec3(std::stoi(line[lineStart]), std::stoi(line[lineStart + 1]), std::stoi(line[lineStart + 2]));
}

void Editor::LoadLevel(std::string levelName)
{
	std::fstream file;
	std::string line;
	std::vector<std::string> parsedLine;
	EnemySpawner* newEnemySpawner;
	Barrier* newBarrier;
	CharacterSelector* newCharSelector;
	LevelEnd* newLevelEnd;
	NavNode* newNavNode;
	PressurePlate* newPressurePlate;
	Door* newDoor;
	EntityType entType = _none;

	newEnemySpawner = dynamic_cast<EnemySpawner*>(enemySpawner->Copy());
	newLevelEnd = dynamic_cast<LevelEnd*>(levelEnd->Copy());
	newBarrier = dynamic_cast<Barrier*>(barrier->Copy());
	newCharSelector = dynamic_cast<CharacterSelector*>(characterSelector->Copy());
	newNavNode = dynamic_cast<NavNode*>(navNode->Copy());
	newPressurePlate = dynamic_cast<PressurePlate*>(pressurePlate->Copy());
	newDoor = dynamic_cast<Door*>(door->Copy());

	delete(newEnemySpawner);
	delete(newLevelEnd);
	delete(newBarrier);
	delete(newCharSelector);
	delete(newNavNode);
	delete(newPressurePlate);
	delete(newDoor);
	canOptInOut = false;

	file.open(levelName.c_str());
	if (!file.is_open())
	{
		std::cout << "File " << levelName << " failed to open.\n";
		return;
	}
	std::cout << "Level " << levelName << " loaded.\n";
	scale = defaultScale;
	while (std::getline(file, line))
	{
		Parser(line, parsedLine);
		if (parsedLine.size() == 0) { continue; }
		if (parsedLine[0][0] == '*') { inComment = !inComment; }
		if (inComment) { continue; }
		//if (parsedLine[0] == "#CanOptIn") { canOptInOut = true; }
		if(parsedLine[0]=="#SetScale" && parsedLine.size() > 1){scale = (float)std::stoi(parsedLine[1]);}
		if (entityTypes.count(parsedLine[0]) == 1) 
		{
			entType = entityTypes[parsedLine[0]];
			//std::cout << parsedLine[0] << "\n";
			switch (entType)
			{
			case Editor::_playerSpawner:
				break;
			case Editor::_enemySpawner:
				newEnemySpawner = dynamic_cast<EnemySpawner*>(enemySpawner->Copy());
				initQueue.push_back(newEnemySpawner);
				enemySpawners.push_back(newEnemySpawner);
				break;
			case Editor::_barrier:
				newBarrier = dynamic_cast<Barrier*>(barrier->Copy());
				initQueue.push_back(newBarrier);
				barriers.push_back(newBarrier);
				break;
			case Editor::_navNode:
				newNavNode = dynamic_cast<NavNode*>(navNode->Copy());
				initQueue.push_back(newNavNode);
				navNodes.push_back(newNavNode);
				break;
			case Editor::_characterSelector:
				newCharSelector = dynamic_cast<CharacterSelector*>(characterSelector->Copy());
				initQueue.push_back(newCharSelector);
				characterSelectors.push_back(newCharSelector);
				break;
			case Editor::_levelEnd:
				newLevelEnd = dynamic_cast<LevelEnd*>(levelEnd->Copy());
				initQueue.push_back(newLevelEnd);
				levelEnds.push_back(newLevelEnd);
				break;
			case Editor::_pressurePlate:
				newPressurePlate = dynamic_cast<PressurePlate*>(pressurePlate->Copy());
				initQueue.push_back(newPressurePlate);
				pressurePlates.push_back(newPressurePlate);
				break;
			case Editor::_door:
				newDoor = dynamic_cast<Door*>(door->Copy());
				initQueue.push_back(newDoor);
				doors.push_back(newDoor);/**/
				break;
			case Editor::_none:
				break;
			default:
				break;
			}/**/
		}
		else 
		{
			switch (entType)
			{
			case Editor::_playerSpawner:
				if (parsedLine[0] == "Position")
				{
					levelStart->transform.position = GetVec3(parsedLine, 1);
					levelStart->transform.position *= scale;
				}
				else if (parsedLine[0] == "Scale")
				{
					SetEntScale(&levelStart->boundingBox.transform, parsedLine, 1);
				}
				break;
			case Editor::_enemySpawner:
				if (parsedLine[0] == "Position")
				{
					SetEntPosition(newEnemySpawner, parsedLine, 1);
					newEnemySpawner->transform.position *= scale;
				}
				else if (parsedLine[0] == "Scale")
				{
					SetEntScale(&newEnemySpawner->transform, parsedLine, 1);
				}
				else if (parsedLine[0] == "Radius")
				{
					newEnemySpawner->radius = (float)std::stoi(parsedLine[1]) * scale;
				}
				else if (parsedLine[0] == "WaveSize")
				{
					newEnemySpawner->waveSize = std::stoi(parsedLine[1]);
				}
				else if (parsedLine[0] == "WaveIncrement")
				{
					newEnemySpawner->waveIncrement = std::stoi(parsedLine[1]);
				}
				else if (parsedLine[0] == "NumberOfWaves")
				{
					newEnemySpawner->numberOfWaves = std::stoi(parsedLine[1]);
				}
				else if (parsedLine[0] == "ChargerChance")
				{
					newEnemySpawner->chargeProb= (float)std::stoi(parsedLine[1]);
				}
				else if (parsedLine[0] == "ThrowerChance")
				{
					newEnemySpawner->throwProb = (float)std::stoi(parsedLine[1]);
				}
				else if (parsedLine[0] == "BomberChance")
				{
					newEnemySpawner->bombProb = (float)std::stoi(parsedLine[1]);
				}
				break;
			case Editor::_barrier:
				if (parsedLine[0] == "Position")
				{
					SetEntPosition(newBarrier, parsedLine, 1);
					newBarrier->transform.position *= scale;
				}
				else if (parsedLine[0] == "Scale")
				{
					SetEntScale(&newBarrier->transform, parsedLine, 1);
					newBarrier->transform.scale *= (scale / defaultScale);
					newBarrier->boundingBox.transform.scale = newBarrier->transform.scale * defaultScale;
				}
				else if (parsedLine[0] == "SetMaterial" && parsedLine.size() > 1)
				{
					newBarrier->materialPtr = assetManager->GetMaterial(parsedLine[1]);
				}
				break;
			case Editor::_navNode:
				if (parsedLine[0] == "Position")
				{
					SetEntPosition(newNavNode, parsedLine, 1);
					newNavNode->transform.position *= scale;
				}
				break;
			case Editor::_characterSelector:
				if (parsedLine[0] == "Position")
				{
					SetEntPosition(newCharSelector, parsedLine, 1);
					newCharSelector->transform.position *= scale;
				}
				else if (parsedLine[0] == "Scale")
				{
					SetEntScale(&newCharSelector->transform, parsedLine, 1);
				}
				else if (parsedLine[0] == "Character")
				{
					if (parsedLine[1] == "red") { newCharSelector->SetCharacter(Actor::red); }
					else if (parsedLine[1] == "ted") { newCharSelector->SetCharacter(Actor::ted); }
					else if (parsedLine[1] == "key") { newCharSelector->SetCharacter(Actor::key); }
					else if (parsedLine[1] == "tan") { newCharSelector->SetCharacter(Actor::tan); }
				}
				else if (parsedLine[0] == "SetMaterial" && parsedLine.size() > 1)
				{
					newCharSelector->materialPtr = assetManager->GetMaterial(parsedLine[1]);
				}
				break;
			case Editor::_levelEnd:
				if (parsedLine[0] == "Position")
				{
					SetEntPosition(newLevelEnd, parsedLine, 1);
					newLevelEnd->transform.position *= scale;
				}
				else if (parsedLine[0] == "Scale")
				{
					SetEntScale(&newLevelEnd->transform, parsedLine, 1);
				}
				else if (parsedLine[0] == "Radius")
				{
					newLevelEnd->radius = (float)std::stoi(parsedLine[1]);
					newLevelEnd->radius *= scale;
				}
				else if (parsedLine[0] == "Locked")
				{
					newLevelEnd->locked = true;
					//lock type is an optional argument
					//level ends can be opened by buttons and such once the event system is in
				}
				else if (parsedLine[0] == "NextLevel")
				{
					newLevelEnd->nextLevel = parsedLine[1];
				}
				else if (parsedLine[0] == "SetMaterial" && parsedLine.size() > 1)
				{
					newLevelEnd->materialPtr = assetManager->GetMaterial(parsedLine[1]);
				}
				else if (parsedLine[0] == "SetOpenMaterial" && parsedLine.size() > 1)
				{
					newLevelEnd->openMatter = assetManager->GetMaterial(parsedLine[1]);
				}
				else if (parsedLine[0] == "SetClosedMaterial" && parsedLine.size() > 1)
				{
					newLevelEnd->closedMatter = assetManager->GetMaterial(parsedLine[1]);
				}
				break;/**/
			case Editor::_pressurePlate:
				if (parsedLine[0] == "Position")
				{
					SetEntPosition(newPressurePlate, parsedLine, 1);
					newPressurePlate->transform.position *= scale;
				}
				else if (parsedLine[0] == "Target" && parsedLine.size() > 1)
				{
					newPressurePlate->targetAliases.push_back(parsedLine[1]);
				}
				else if (parsedLine.size() > 1 && parsedLine[0] == "Message")
				{
					newPressurePlate->SetMessage(parsedLine[1]);
				}
				else if (parsedLine[0] == "SetMaterial" && parsedLine.size() > 1)
				{
					newPressurePlate->materialPtr = assetManager->GetMaterial(parsedLine[1]);
				}
				else if (parsedLine[0] == "SetUpMaterial" && parsedLine.size() > 1)
				{
					newPressurePlate->upMatter = assetManager->GetMaterial(parsedLine[1]);
				}
				else if (parsedLine[0] == "SetDownMaterial" && parsedLine.size() > 1)
				{
					newPressurePlate->downMatter = assetManager->GetMaterial(parsedLine[1]);
				}
				break;
			case Editor::_door:
				if (parsedLine[0] == "Position")
				{
					SetEntPosition(newDoor, parsedLine, 1);
					newDoor->transform.position *= scale;
					newDoor->SetClosedPos(newDoor->transform.position);
					newDoor->SetClosed();
				}
				else if (parsedLine[0] == "Scale")
				{
					SetEntScale(&newDoor->transform, parsedLine, 1);
					newDoor->boundingBox.transform.scale = newDoor->transform.scale * scale;
				}
				if (parsedLine.size() > 1 && parsedLine[0] == "Name")
				{
					newDoor->alias = parsedLine[1];
				}
				else if (parsedLine[0] == "Closed" && parsedLine.size() > 3)
				{
					newDoor->SetClosedPos(GetVec3(parsedLine, 1)*scale);
				}
				else if (parsedLine[0] == "Open" && parsedLine.size() > 3)
				{
					newDoor->SetOpenPos(GetVec3(parsedLine, 1)*scale);
				}/**/
				else if (parsedLine[0] == "StartOpen")
				{
					newDoor->Open();
					newDoor->SetOpen();
				}
				else if (parsedLine[0] == "Speed" && parsedLine.size() > 1)
				{
					newDoor->SetSpeed((float)std::stoi(parsedLine[1]) * scale);
				}
				else if (parsedLine[0] == "SetMaterial" && parsedLine.size() > 1)
				{
					newDoor->materialPtr = assetManager->GetMaterial(parsedLine[1]);
				}
				break;
			case Editor::_none:
				continue;
				break;
			default:
				break;
			}
		}
	}
	file.close();
	//link event system
	PressurePlate* myPlate;
	for (size_t i = 0; i < pressurePlates.size(); i++)
	{
		myPlate = dynamic_cast<PressurePlate*>(pressurePlates[i]);
		for (size_t f = 0; f < myPlate->targetAliases.size(); f++)
		{
			for (size_t g = 0; g < doors.size(); g++)
			{
				if (doors[g]->alias == myPlate->targetAliases[f])
				{
					myPlate->AddTarget(doors[g]);
				}
			}
		}
	}
}

/*void Editor::LoadLevel(std::string levelName)
{
	std::fstream file;
	std::string line;
	std::vector<std::string> parsedLine;
	file.open(levelName.c_str());
	EnemySpawner* newEnemySpawner;
	Barrier* newBarrier;
	CharacterSelector* newCharSelector;
	LevelEnd* newLevelEnd;
	int argIndex = 0;
	canOptInOut = false;
	if (!file.is_open())
	{
		std::cout << "File " << levelName << " failed to open.\n";
		return;
	}
	std::cout << "Level " << levelName << " loaded.\n";
	while (std::getline(file, line))
	{
		Parser(line, parsedLine);
		if (parsedLine.size() == 0) { continue; }
		argIndex = 1;
		//Entity* newEnt;
		if (parsedLine[0][0] == '#')
		{
			if (parsedLine[0] == "#PlayerSpawner")
			{
				SetEntPosition(levelStart, parsedLine, argIndex);
			}
			else if (parsedLine[0] == "#EnemySpawner")
			{
				newEnemySpawner = dynamic_cast<EnemySpawner*>(enemySpawner->Copy());
				SetEntPosition(newEnemySpawner, parsedLine, argIndex);
				initQueue.push_back(newEnemySpawner);
				enemySpawners.push_back(newEnemySpawner);
				if (parsedLine.size() > argIndex)
				{
					newEnemySpawner->radius = std::stoi(parsedLine[argIndex]);
				}
				argIndex++;
				if (parsedLine.size() > argIndex)
				{
					newEnemySpawner->waveSize = std::stoi(parsedLine[argIndex]);
				}
				argIndex++;
				if (parsedLine.size() > argIndex)
				{
					newEnemySpawner->waveIncrement = std::stoi(parsedLine[argIndex]);
				}
				argIndex++;
				if (parsedLine.size() > argIndex)
				{
					newEnemySpawner->numberOfWaves = std::stoi(parsedLine[argIndex]);
				}
			}
			else if (parsedLine[0] == "#Barrier")
			{
				newBarrier = dynamic_cast<Barrier*>(barrier->Copy());
				SetEntPosition(newBarrier, parsedLine, argIndex); 
				SetEntScale(newBarrier, parsedLine, argIndex);
				newBarrier->boundingBox.transform.scale = newBarrier->transform.scale*50.0f;
				initQueue.push_back(newBarrier);
				barriers.push_back(newBarrier);
			}
			else if (parsedLine[0] == "#LevelEnd")
			{
				newLevelEnd = dynamic_cast<LevelEnd*>(levelEnd->Copy());
				SetEntPosition(newLevelEnd, parsedLine, argIndex);
				newLevelEnd->nextLevel = parsedLine[7];
				newLevelEnd->radius = std::stoi(parsedLine[8]);
				if (parsedLine[9] == "locked")
				{
					newLevelEnd->locked = true;
				}
				initQueue.push_back(newLevelEnd);
				levelEnds.push_back(newLevelEnd);
			}
			else if (parsedLine[0] == "#CharacterSelector")
			{
				newCharSelector = dynamic_cast<CharacterSelector*>(characterSelector->Copy());
				SetEntPosition(newCharSelector, parsedLine, argIndex);
				SetEntScale(newCharSelector, parsedLine, argIndex);
				if (parsedLine[7] == "red") { newCharSelector->SetCharacter(Actor::red); }
				else if (parsedLine[7] == "tan") { newCharSelector->SetCharacter(Actor::tan); }
				else if (parsedLine[7] == "key") { newCharSelector->SetCharacter(Actor::key); }
				else if (parsedLine[7] == "ted") { newCharSelector->SetCharacter(Actor::ted); }
				initQueue.push_back(newCharSelector);
				characterSelectors.push_back(newCharSelector);
			}
			else if (parsedLine[0] == "#OptInOut")
			{
				canOptInOut = true;
			}
		}
	}
	file.close();
}/**/