// MercutioEngine.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "meEngine.h"
#include "meMath.h"
#include "meWorld.h"
#include "meActor.h"
#include "meAssetManager.h"
#include "meText.h"
#include "meMenu.h"
#include "meCamera.h"
#include "meEnemy.h"
#include "meRender.h"
#include "meProjectile.h"
#include "meEnemyAggro.h"
#include "meSceneManager.h"
#include "meBarrier.h"
#include "meInput.h"
#include "meCharacterSelector.h"
#include "wokEditor.h"
#include "wokEnemySpawner.h"
#include "wokSpawnWarning.h"
#include "wokLevelEnd.h"
#include "wokNavNode.h"
#include "wokPressurePlate.h"
#include "wokDoor.h"
#include "meMenuManager.h"

int main()
{
	World world = World();

	glfwInit();

	AssetManager assetManager;

	glm::mat4 meshMatrix;
	meshMatrix = glm::scale(meshMatrix, glm::vec3(1, 0.25, 1));
	assetManager.CreateMesh("chopstick", "quad", meshMatrix);
	meshMatrix = glm::mat4();
	meshMatrix = glm::scale(meshMatrix, glm::vec3(0.25, 1, 1));
	assetManager.CreateMesh("exclamation", "quad", meshMatrix);

	assetManager.LoadShader("simple", "assets/shaders/simple.vert", "assets/shaders/simple.frag");
	assetManager.LoadShader("text", "assets/shaders/text.vert", "assets/shaders/text.frag");
	assetManager.LoadShader("wireframe", "assets/shaders/wireframe.vert", "assets/shaders/wireframe.frag");
	assetManager.LoadShader("scaled", "assets/shaders/scaled.vert", "assets/shaders/simple.frag");
	assetManager.LoadShader("animated", "assets/shaders/animated.vert", "assets/shaders/simple.frag");

	assetManager.LoadTextures();

	assetManager.LoadSoundBuffer("assets/sound_effects/shoot.wav", "shoot");

	assetManager.CreateFont("arial200", "assets/fonts/arial.ttf", 0, 200);
	assetManager.CreateFont("arial80", "assets/fonts/arial.ttf", 0, 100);

	Renderer renderer(&world, assetManager.window);
	renderer.debugShader = assetManager.GetShader("wireframe");

	InputManager inputManager;
	inputManager.ParseInputConfig("assets/input_config.txt");
	double pulseDelay = 0.5;
	double pulseLength = 0.2;
	inputManager.AddButton("debug");
	inputManager.ButtonAddKeyPress("debug", GLFW_KEY_T);

	inputManager.AddButton("suicide");
	inputManager.ButtonAddKeyPress("suicide", GLFW_KEY_R);
	inputManager.ButtonAddJoyButtonPress("suicide", 6, false);
	inputManager.BuildControllers();
	
	SceneManager* sceneManager = new SceneManager();
	sceneManager->spawning = false;
	world.AddEntity(sceneManager);/**/

	Entity* terrain = new Entity();
	terrain->meshPtr = assetManager.GetMesh("terrain");
	terrain->materialPtr = assetManager.GetMaterial("floor");
	terrain->transform.position = glm::vec3(0, 0, -10);
	world.AddEntity(terrain);

	Barrier* barrier = new Barrier();
	barrier->meshPtr = assetManager.GetMesh("quad");
	barrier->materialPtr = assetManager.GetMaterial("wall");
	barrier->transform.position = glm::vec3(0, 0, -9);
	barrier->collides = true;
	world.AddPrototype(barrier);/**/

	PressurePlate* pressurePlate = new PressurePlate();
	pressurePlate->meshPtr = assetManager.GetMesh("quad");
	pressurePlate->materialPtr = assetManager.GetMaterial("PressurePlateOff");
	pressurePlate->downMatter = assetManager.GetMaterial("PressurePlateOff");
	pressurePlate->upMatter = assetManager.GetMaterial("PressurePlateOn");
	pressurePlate->collides = true;
	pressurePlate->transform.scale *= 3;
	pressurePlate->boundingBox.transform.scale *= 2;
	world.AddPrototype(pressurePlate);

	Door* door = new Door();
	door->meshPtr= assetManager.GetMesh("quad");
	door->materialPtr= assetManager.GetMaterial("wall");
	door->tags.insert("door");
	door->collides = true;
	door->transform.position = glm::vec3(0, 0, -9);
	world.AddPrototype(door);

	Actor* actor = new Actor();
	actor->physObject.bounceType = PhysObject::slide;
	actor->layer = Entity::player;
	actor->tags.insert("hero");
	actor->materialPtr = assetManager.GetMaterial("red");
	actor->meshPtr = assetManager.GetMesh("quad");
	actor->shootSound.setBuffer(*assetManager.GetSoundBuffer("shoot"));
	actor->transform.scale *= 2.0f;
	actor->collides = true;
	actor->redMatter = assetManager.GetMaterial("red");
	actor->tedMatter = assetManager.GetMaterial("ted");
	actor->keyMatter = assetManager.GetMaterial("key");
	actor->tanMatter = assetManager.GetMaterial("tan");
	actor->ninjaMatter= assetManager.GetMaterial("ninja");
	actor->controller = inputManager.aggregateController;
	actor->numFrames = 3;
	actor->currentFrame = 1;
	actor->flip = -1.0f;
	world.AddPrototype(actor);

	Entity* belt1 = new Entity();
	belt1->layer = Entity::belt;
	belt1->tags.insert("belt");
	belt1->localTransform.position = glm::vec3(0, 0, 1);
	belt1->meshPtr= assetManager.GetMesh("ninja");
	belt1->materialPtr = assetManager.GetMaterial("belt1");
	belt1->transform.scale *= 1.0f;
	belt1->SetParent(actor);
	belt1->isVisible = false;
	world.AddPrototype(belt1);

	Entity* belt2 = belt1->Copy();
	belt2->materialPtr= assetManager.GetMaterial("belt2");
	belt2->SetParent(actor);
	world.AddPrototype(belt2);

	Entity* belt3 = belt1->Copy();
	belt3->materialPtr = assetManager.GetMaterial("belt3");
	belt3->SetParent(actor);
	world.AddPrototype(belt3);

	Entity* belt4 = belt1->Copy();
	belt4->materialPtr = assetManager.GetMaterial("belt4");
	belt4->SetParent(actor);
	world.AddPrototype(belt4);

	Entity* belt5 = belt1->Copy();
	belt5->materialPtr = assetManager.GetMaterial("belt5");
	belt5->SetParent(actor);
	world.AddPrototype(belt5);

	Entity* staticP = new Entity();
	staticP->layer = Entity::static_projectile;
	staticP->SetAwake(false);
	world.AddPrototype(staticP);/**/

	Projectile* projectile = new Projectile();
	projectile->layer = Entity::live_projectiles;
	projectile->tags.insert("projectile");
	projectile->tags.insert("hero");
	projectile->meshPtr = assetManager.GetMesh("wok");
	projectile->materialPtr = assetManager.GetMaterial("wok");
	projectile->isTrigger = true;
	projectile->localTransform.position = glm::vec3(0.0f, 0.0f, -5.0f);
	projectile->SetAwake(false);
	projectile->physObject.drag = 5;
	projectile->staticP = staticP;
	projectile->speed = 1200;
	world.AddPrototype(projectile);/**/

	//add projectiles to actor. actors no longer spawn their own
	Projectile* nProjectile;

	nProjectile = dynamic_cast<Projectile*>(projectile->Copy());
	nProjectile->SetParent(actor);
	world.AddPrototype(nProjectile);

	nProjectile = dynamic_cast<Projectile*>(projectile->Copy());
	nProjectile->SetParent(actor);
	world.AddPrototype(nProjectile);

	nProjectile = dynamic_cast<Projectile*>(projectile->Copy());
	nProjectile->SetParent(actor);
	world.AddPrototype(nProjectile);

	nProjectile = dynamic_cast<Projectile*>(projectile->Copy());
	nProjectile->SetParent(actor);
	world.AddPrototype(nProjectile);

	nProjectile = dynamic_cast<Projectile*>(projectile->Copy());
	nProjectile->SetParent(actor);
	world.AddPrototype(nProjectile);

	Entity* wave = new Entity();
	wave->layer = Entity::player;
	wave->materialPtr = assetManager.GetMaterial("wave");
	wave->meshPtr = assetManager.GetMesh("quad");
	wave->transform.scale *= 2;
	actor->wave = wave;
	wave->SetAwake(false);
	wave->SetParent(actor);
	world.AddPrototype(wave);

	Projectile* wok = dynamic_cast<Projectile*>(projectile->Copy());
	wok->physObject.bounceType = PhysObject::slide;
	world.AddPrototype(wok);
	actor->wok = wok;

	Projectile* chopstick = dynamic_cast<Projectile*>(projectile->Copy());
	chopstick->meshPtr = assetManager.GetMesh("chopstick");
	chopstick->materialPtr = assetManager.GetMaterial("chopstick");
	chopstick->boundingBox.transform.scale *= 0.1f;
	chopstick->speed = 2000.0f;
	world.AddPrototype(chopstick);
	actor->chopstick = chopstick;

	Projectile* spoon = dynamic_cast<Projectile*>(projectile->Copy());
	spoon->meshPtr = assetManager.GetMesh("quad");
	spoon->materialPtr = assetManager.GetMaterial("spoon");
	spoon->physObject.drag = 16;
	spoon->boundingBox.transform.scale *= 0.1f;
	world.AddPrototype(spoon);
	actor->spoon = spoon;

	Projectile* roller = dynamic_cast<Projectile*>(projectile->Copy());
	roller->meshPtr = assetManager.GetMesh("quad");
	roller->materialPtr = assetManager.GetMaterial("rolling_pin");
	roller->health = 6;
	roller->tags.insert("bounce");
	roller->physObject.bounceType = PhysObject::bounce;
	roller->physObject.drag = 2;
	roller->speed = 800.0f;
	world.AddPrototype(roller);
	actor->roller = roller;

	Enemy* enemy = new Enemy();
	enemy->layer = Entity::enemy;
	enemy->tags.insert("bad");
	enemy->transform.scale = glm::vec3(3.0f);
	enemy->materialPtr = assetManager.GetMaterial("goblin");
	enemy->meshPtr = assetManager.GetMesh("quad");
	enemy->collides = true;
	enemy->boundingBox.transform.scale *= 2.0f;
	enemy->boundingBox.debugColor = glm::vec3(1, 0, 0);
	world.AddPrototype(enemy);

	Entity* monsterSpawn = new Entity();
	monsterSpawn->isVisible = false;
	monsterSpawn->layer = Entity::enemy;
	monsterSpawn->transform.position = glm::vec3(0.0f, 0.0f, -1.0f);
	monsterSpawn->materialPtr = assetManager.GetMaterial("monster_spawn");
	monsterSpawn->meshPtr= assetManager.GetMesh("quad");
	monsterSpawn->SetAwake(false);
	world.AddPrototype(monsterSpawn);

	EnemyAggro* enemyAggro = new EnemyAggro();
	enemyAggro->collides = true;
	enemyAggro->isTrigger = true;
	enemyAggro->boundingBox.transform.scale *= 80;
	enemy->enemyAggro = enemyAggro;
	enemyAggro->SetParent(enemy);
	world.AddPrototype(enemyAggro);

	Entity* enemyNotice = new Entity();
	enemyNotice->layer = Entity::ui;
	enemyNotice->materialPtr = assetManager.GetMaterial("exclamation");
	enemyNotice->meshPtr = assetManager.GetMesh("exclamation");
	enemyNotice->localTransform.position = glm::vec3(0, 50, 1);
	enemyNotice->SetAwake(false);
	enemyNotice->SetParent(enemy);
	world.AddPrototype(enemyNotice);

	Projectile* enemyProjectile = new Projectile();
	enemyProjectile->layer = Entity::live_projectiles;
	enemyProjectile->tags.insert("projectile");
	enemyProjectile->meshPtr = assetManager.GetMesh("quad");
	enemyProjectile->materialPtr = assetManager.GetMaterial("spear");
	enemyProjectile->SetParent(enemy);
	enemyProjectile->isTrigger = true;
	enemyProjectile->collides = false;
	enemyProjectile->kinematic = false;
	enemyProjectile->targetTag = "hero";
	enemyProjectile->SetAwake(false);
	enemyProjectile->physObject.drag = 5;
	enemyProjectile->transform.scale *= 3.0f;
	enemyProjectile->boundingBox.transform.scale *= 0.1;
	world.AddPrototype(enemyProjectile);

	Entity* bombTarget = new Entity();
	bombTarget->layer = Entity::ui;
	bombTarget->meshPtr = assetManager.GetMesh("quad");
	bombTarget->materialPtr = assetManager.GetMaterial("bomb_target");
	bombTarget->SetParent(enemy);
	bombTarget->SetAwake(false);
	bombTarget->isTrigger = true;
	bombTarget->transform.scale *= 2.0f;
	world.AddPrototype(bombTarget);

	Projectile* enemyBomb = dynamic_cast<Projectile*>(enemyProjectile->Copy());
	enemyBomb->meshPtr = assetManager.GetMesh("quad");
	enemyBomb->tags.insert("bomb");
	enemyBomb->materialPtr = assetManager.GetMaterial("pork_bun");
	enemyBomb->boundingBox.transform.scale *= 0.25f;
	enemyBomb->explodes = true;
	enemyBomb->explodeMatter = assetManager.GetMaterial("bomb_explosion");
	enemyBomb->SetParent(enemy);
	world.AddPrototype(enemyBomb);

	Entity* enemyBody = new Entity();
	enemyBody->isVisible = false;
	enemyBody->layer = Entity::dead_enemy;
	enemyBody->transform.scale = glm::vec3(1.5f);
	enemyBody->materialPtr = assetManager.GetMaterial("goblin_dead");
	enemyBody->meshPtr = assetManager.GetMesh("quad");
	enemy->body = enemyBody;
	world.AddPrototype(enemyBody);/**/

	Entity* enemyArmoredBody = new Entity();
	enemyArmoredBody->isVisible = false;
	enemyArmoredBody->layer = Entity::dead_enemy;
	enemyArmoredBody->materialPtr = assetManager.GetMaterial("armored_goblin_dead");
	enemyArmoredBody->meshPtr = assetManager.GetMesh("quad");
	enemyArmoredBody->transform.scale = glm::vec3(1);
	world.AddPrototype(enemyArmoredBody);/**/

	Entity* bomberBody = new Entity();
	bomberBody->isVisible = false;
	bomberBody->layer = Entity::dead_enemy;
	bomberBody->materialPtr = assetManager.GetMaterial("bomber_dead");
	bomberBody->meshPtr = assetManager.GetMesh("quad");
	bomberBody->transform.scale = glm::vec3(4.0f);
	world.AddPrototype(bomberBody);/**/

	Enemy* thrower = dynamic_cast<Enemy*>(enemy->Copy());
	thrower->body = enemyArmoredBody;
	thrower->materialPtr = assetManager.GetMaterial("armored_goblin");
	thrower->attackRange = 1400.0f;
	thrower->persueRange = 1200.0f;
	thrower->transform.scale = glm::vec3(2.0f);
	thrower->type = Enemy::thrower;
	world.AddPrototype(thrower);

	Enemy* bomber = dynamic_cast<Enemy*>(enemy->Copy());
	bomber->materialPtr = assetManager.GetMaterial("bomber");
	bomber->transform.scale = glm::vec3(4.0f);
	bomber->boundingBox.transform.scale *= 2.0f;
	bomber->body = bomberBody;
	//enemy->boundingBox.transform.scale *= 2.0f;
	bomber->type = Enemy::bomber;
	world.AddPrototype(bomber);

	Camera* camera = new Camera();
	camera->transform.position = glm::vec3(0, 0, 10);
	camera->input = &inputManager;
	world.AddCamera(camera);

	Text* text = new Text();
	text->layer = Entity::ui;
	text->font = assetManager.GetFont("arial80");
	text->shader = assetManager.GetShader("text");
	text->color = glm::vec3(0, 0, 0);
	world.AddPrototype(text);

	Menu* menu = new Menu();
	menu->controller = inputManager.aggregateController;
	menu->lowestIndex = 0;
	menu->selectedIndex = 0;
	world.AddPrototype(menu);

	MenuManager* menuManager = new MenuManager();
	menuManager->localTransform.position = glm::vec3(-960, 450, -1);
	menuManager->text = text;
	menuManager->menu = menu;
	menuManager->titleFont = assetManager.GetFont("arial200");
	menuManager->SetParent(camera);
	menuManager->CreateMenus("assets/menus/other.txt");
	menuManager->sceneManager = sceneManager;
	sceneManager->menuManager = menuManager;
	world.AddEntity(menuManager);

	Text* timeSurvived = new Text();
	timeSurvived->layer = Entity::ui;
	timeSurvived->font = assetManager.GetFont("arial80");
	timeSurvived->shader = assetManager.GetShader("text");
	timeSurvived->text = "TIME: ";
	timeSurvived->color = glm::vec3(0, 0, 0);
	timeSurvived->SetParent(camera);
	timeSurvived->SetAwake(false);
	timeSurvived->localTransform.position= glm::vec3(-1700, 900, -1);
	world.AddEntity(timeSurvived);

	Text* killCount = new Text();
	killCount->font = assetManager.GetFont("arial80");
	killCount->shader = assetManager.GetShader("text");
	killCount->text = "ENEMIES KILLED: ";
	killCount->color = glm::vec3(0, 0, 0);
	killCount->SetAwake(false);
	killCount->SetParent(camera);
	killCount->localTransform.position = glm::vec3(-1700, 600, -1);
	world.AddEntity(killCount);

	CharacterSelector* charSelector = new CharacterSelector();
	charSelector->isTrigger = true;
	charSelector->collides = true;
	charSelector->transform.scale *= 5;
	charSelector->boundingBox.transform.scale *= 4;
	charSelector->meshPtr = assetManager.GetMesh("quad");
	charSelector->materialPtr = assetManager.GetMaterial("wormhole");
	charSelector->materials.push_back(assetManager.GetMaterial("red_select"));
	charSelector->materials.push_back(assetManager.GetMaterial("ted_select"));
	charSelector->materials.push_back(assetManager.GetMaterial("tan_select"));
	charSelector->materials.push_back(assetManager.GetMaterial("key_select"));
	charSelector->materials.push_back(assetManager.GetMaterial("wormhole"));
	world.AddPrototype(charSelector);

	SpawnWarning* spawnWarning = new SpawnWarning();
	spawnWarning->materialPtr = assetManager.GetMaterial("monster_spawn");
	spawnWarning->meshPtr = assetManager.GetMesh("quad");
	world.AddPrototype(spawnWarning);

	EnemySpawner* enemySpawner = new EnemySpawner();
	enemySpawner->materialPtr = assetManager.GetMaterial("EnemySpawner");
	enemySpawner->meshPtr = assetManager.GetMesh("quad");
	enemySpawner->transform.scale *= 2;
	enemySpawner->charger = enemy;
	enemySpawner->thrower = thrower;
	enemySpawner->bomber = bomber;
	enemySpawner->isVisible = false;
	enemySpawner->spawnWarning = spawnWarning;
	world.AddPrototype(enemySpawner);

	NavNode* navNode = new NavNode();
	navNode->materialPtr = assetManager.GetMaterial("NavNode");
	navNode->meshPtr = assetManager.GetMesh("quad");
	world.AddPrototype(navNode);

	Editor* editor = new Editor();
	editor->barrier = barrier;
	world.AddEntity(editor);
	editor->enemySpawner = enemySpawner;
	editor->SetParent(sceneManager);
	editor->characterSelector = charSelector;
	editor->navNode = navNode;
	editor->pressurePlate = pressurePlate;
	editor->door = door;
	editor->assetManager = &assetManager;

	Entity* levelStart = new Entity();
	levelStart->isVisible = false;
	levelStart->materialPtr = assetManager.GetMaterial("PlayerSpawner");
	levelStart->meshPtr = assetManager.GetMesh("quad");
	levelStart->boundingBox.transform.scale *= 2;
	editor->levelStart = levelStart;
	//levelStart->isVisible = false;
	world.AddEntity(levelStart);

	LevelEnd* levelEnd = new LevelEnd();
	levelEnd->materialPtr = assetManager.GetMaterial("wormhole_closed");
	levelEnd->meshPtr = assetManager.GetMesh("quad");
	levelEnd->closedMatter = assetManager.GetMaterial("wormhole_closed");
	levelEnd->openMatter = assetManager.GetMaterial("wormhole");
	levelEnd->transform.scale *= 4;
	editor->levelEnd = levelEnd;
	world.AddPrototype(levelEnd);

	sceneManager->enemy = enemy;
	sceneManager->red = actor;
	sceneManager->camera = camera;
	sceneManager->barrier = barrier;
	sceneManager->enemiesKilledText = killCount;
	sceneManager->survivedTimeText = timeSurvived;
	sceneManager->inputManager = &inputManager;
	sceneManager->characterSelector = charSelector;
	sceneManager->armoredEnemyMatter = assetManager.GetMaterial("armored_goblin");
	sceneManager->monsterSpawn = monsterSpawn;
	sceneManager->editor = editor;

	Engine engine(&world, &assetManager, &renderer);
	engine.inputManager = &inputManager;

	while (engine.GameRunning())
	{
		engine.Update();
	}

	glfwTerminate();
	
	return 0;
}

