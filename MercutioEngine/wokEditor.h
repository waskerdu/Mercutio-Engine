#pragma once
#include "meEntity.h"
#include "meAssetManager.h"
class Editor :
	public Entity
{
	//std::vector<Entity*> levelEnds;
	std::vector<Entity*> navNodes;
	std::vector<Entity*> enemySpawners;
	std::vector<Entity*> barriers;
	std::vector<Entity*> characterSelectors;
	std::vector<Entity*> pressurePlates;
	std::vector<Entity*> doors;
	std::vector<std::vector<Entity*>> navMesh;
	
	enum EntityType
	{
		_playerSpawner,
		_enemySpawner,
		_barrier,
		_navNode,
		_characterSelector,
		_levelEnd,
		_pressurePlate,
		_door,
		_none
	};
	enum ArgumentType
	{
		_position,
		_scale,
		_radius,
		_waveSize,
		_waveIncriment,
		_numberOfWaves,
		_locked,
		_character,
		_level
	};
	std::map<std::string, EntityType> entityTypes;
	std::map<std::string, ArgumentType> argumentTypes;

	float scale = 50.0f;
	const float defaultScale = 50.0f;
	bool inComment = false;
public:
	std::vector<Entity*> levelEnds;
	Entity* navNode;
	Entity* levelStart;
	Entity* levelEnd;
	Entity* enemySpawner;
	Entity* barrier;
	Entity* characterSelector;
	Entity* pressurePlate;
	Entity* door;
	AssetManager* assetManager;
	bool editMode = false;
	bool canOptInOut = false;
private:
	void PlaceBariers();
	void PlaceSpawners();
	void PlaceLevelEnds();
	void PlaceNavNodes();
	void AutoGenerateNavMesh();
	void RecalculateNavNode();
	void RecalculateNavMesh();
	void LoadNavMesh();
	bool IsNavMeshValid();
	void SetEntPosition(Entity* ent, std::vector<std::string> line, int &lineStart);
	void SetEntPosition(Entity* ent, std::vector<std::string> line, int lineStart);
	void SetEntScale(Entity* ent, std::vector<std::string> line, int &lineStart);
	void SetEntScale(Transform* trans, std::vector<std::string> line, int lineStart);
	glm::vec3 GetVec3(std::vector<std::string> line, int lineStart);
public:
	Editor();
	~Editor();
	void LoadLevel(std::string levelName);
	void SaveLevel();
	void SaveAsLevel();
	void Reset();
	void Update();
	void GetEnemies(std::vector<Entity*>*);
	bool Wave();
	void GetStartPos(glm::vec3* pos);
	bool NeedsWave();
};

