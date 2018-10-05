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
	//if (inputManager.ParseInputConfig("assets/input_config.txt") == false)
	if(true)
	{
		double pulseDelay = 0.5;
		double pulseLength = 0.2;
		inputManager.AddButton("debug");
		inputManager.ButtonAddKeyPress("debug", GLFW_KEY_T);

		inputManager.AddButton("suicide");
		inputManager.ButtonAddKeyPress("suicide", GLFW_KEY_R);
		inputManager.ButtonAddJoyButtonPress("suicide", 6, false);

		/*inputManager.AddButton("menuConfirm");
		inputManager.ButtonAddKeyPress("menuConfirm", GLFW_KEY_ENTER);
		inputManager.ButtonAddKeyPress("menuConfirm", GLFW_KEY_SPACE);
		inputManager.ButtonAddJoyButtonPress("menuConfirm", 0, false);
		inputManager.ButtonAddJoyButtonPress("menuConfirm", 1, true);/**/

		/*inputManager.AddButton("menuCancel");
		inputManager.ButtonAddKeyPress("menuCancel", GLFW_KEY_TAB);
		inputManager.ButtonAddJoyButtonPress("menuCancel", 1, false);
		inputManager.ButtonAddJoyButtonPress("menuCancel", 2, true);/**/

		/*inputManager.AddButton("togglePause");
		inputManager.ButtonAddKeyPress("togglePause", GLFW_KEY_ESCAPE);
		inputManager.ButtonAddJoyButtonPress("togglePause", 7, false);
		inputManager.ButtonAddJoyButtonPress("togglePause", 9, true);

		/*inputManager.AddButton("menuUp");
		inputManager.ButtonAddKeyPulse("menuUp", GLFW_KEY_W, pulseLength, pulseDelay);
		inputManager.ButtonAddKeyPulse("menuUp", GLFW_KEY_UP, pulseLength, pulseDelay);
		inputManager.ButtonAddJoyButtonPulse("menuUp", 10, pulseLength, pulseDelay, false);
		inputManager.ButtonAddJoyButtonPulse("menuUp", 14, pulseLength, pulseDelay, true);
		
		inputManager.ButtonAddJoyAxisPulse("menuUp", 1, pulseLength, pulseDelay, -0.5, true, true);

		inputManager.AddButton("menuDown");
		inputManager.ButtonAddKeyPulse("menuDown", GLFW_KEY_S, pulseLength, pulseDelay);
		inputManager.ButtonAddKeyPulse("menuDown", GLFW_KEY_DOWN, pulseLength, pulseDelay);
		inputManager.ButtonAddJoyButtonPulse("menuDown", 12, pulseLength, pulseDelay, false);
		inputManager.ButtonAddJoyButtonPulse("menuDown", 16, pulseLength, pulseDelay, true);
		inputManager.ButtonAddJoyAxisPulse("menuDown", 1, pulseLength, pulseDelay, -0.5, true, false);
		inputManager.ButtonAddJoyAxisPulse("menuDown", 1, pulseLength, pulseDelay, 0.5, false, true);/**/

		/*inputManager.AddButton("menuLeft");
		inputManager.ButtonAddKeyPulse("menuLeft", GLFW_KEY_A, pulseLength, pulseDelay);
		inputManager.ButtonAddKeyPulse("menuLeft", GLFW_KEY_LEFT, pulseLength, pulseDelay);
		inputManager.ButtonAddJoyButtonPulse("menuLeft", 13, pulseLength, pulseDelay, false);
		inputManager.ButtonAddJoyButtonPulse("menuLeft", 17, pulseLength, pulseDelay, true);
		inputManager.ButtonAddJoyAxisPulse("menuLeft", 0, pulseLength, pulseDelay, 0.5, false, false);
		inputManager.ButtonAddJoyAxisPulse("menuLeft", 0, pulseLength, pulseDelay, -0.5, true, true);

		inputManager.AddButton("menuRight");
		inputManager.ButtonAddKeyPulse("menuRight", GLFW_KEY_D, pulseLength, pulseDelay);
		inputManager.ButtonAddKeyPulse("menuRight", GLFW_KEY_RIGHT, pulseLength, pulseDelay);
		inputManager.ButtonAddJoyButtonPulse("menuRight", 11, pulseLength, pulseDelay, false);
		inputManager.ButtonAddJoyButtonPulse("menuRight", 15, pulseLength, pulseDelay, true);
		inputManager.ButtonAddJoyAxisPulse("menuRight", 0, pulseLength, pulseDelay, -0.5, true, false);
		inputManager.ButtonAddJoyAxisPulse("menuDown", 0, pulseLength, pulseDelay, 0.5, false, true);/**/

		/*inputManager.AddButton("dodge");
		inputManager.ButtonAddKeyPress("dodge", GLFW_KEY_LEFT_SHIFT);
		inputManager.ButtonAddJoyButtonPress("dodge", 5, false);
		inputManager.ButtonAddJoyButtonPress("dodge", 7, true);

		inputManager.AddButton("dodge_down");
		inputManager.ButtonAddKeyDown("dodge_down", GLFW_KEY_LEFT_SHIFT);
		inputManager.ButtonAddJoyButtonDown("dodge_down", 5, false);
		inputManager.ButtonAddJoyButtonDown("dodge_down", 7, true);/**/

		/*inputManager.AddAxis2("movement");
		inputManager.Axis2AddJoyAxis("movement", 0, 1, false);
		inputManager.Axis2AddJoyAxis("movement", 0, 1, true);
		inputManager.Axis2AddKey("movement", GLFW_KEY_D, GLFW_KEY_A, GLFW_KEY_W, GLFW_KEY_S);

		inputManager.AddAxis2("aim");
		inputManager.Axis2AddJoyAxis("aim", 2, 3, false);
		inputManager.Axis2AddJoyAxis("aim", 2, 5, true);
		inputManager.Axis2AddKey("aim", GLFW_KEY_RIGHT, GLFW_KEY_LEFT, GLFW_KEY_UP, GLFW_KEY_DOWN);/**/
		inputManager.BuildControllers();

		//inputManager.controllers[0]->SetAxis2Deadzone("movement", 0.5);
	}
	
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
	//actor->transform.scale.y = 1.3f;
	actor->transform.scale *= 2.0f;
	actor->collides = true;
	actor->redMatter = assetManager.GetMaterial("red");
	actor->tedMatter = assetManager.GetMaterial("ted");
	actor->keyMatter = assetManager.GetMaterial("key");
	actor->tanMatter = assetManager.GetMaterial("tan");
	actor->ninjaMatter= assetManager.GetMaterial("ninja");
	actor->controller = inputManager.aggregateController;
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
	//projectile->explodes = true;
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
	//chopstick->explodes = true;
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
	//enemy->navSystem.navPath.push_back(glm::vec3(0, 400, 0));
	//enemy->navSystem.navPath.push_back(glm::vec3(400, 400, 0));
	//enemy->navSystem.navPath.push_back(glm::vec3(400, 0, 0));
	//enemy->navSystem.navPath.push_back(glm::vec3(0, 0, 0));
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

	/*Text* textPtr = new Text();
	textPtr->font = assetManager.GetFont("arial200");
	textPtr->shader = assetManager.GetShader("text");
	textPtr->text = "YOU DIED";
	textPtr->color = glm::vec3(0, 0, 0);
	textPtr->SetAwake(true);
	textPtr->SetParent(camera);
	textPtr->localTransform.position = glm::vec3(-500, 0, -1);
	world.AddEntity(textPtr);*/

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

	Text* gameTitle = new Text();
	gameTitle->font = assetManager.GetFont("arial200");
	gameTitle->shader = assetManager.GetShader("text");
	gameTitle->text = "WOK THE WOK";
	gameTitle->color = glm::vec3(0, 0, 0);
	gameTitle->SetAwake(true);
	world.AddEntity(gameTitle);

	Text* singleplayer = new Text();
	singleplayer->alias = "singleplayer";
	singleplayer->font = assetManager.GetFont("arial80");
	singleplayer->shader = assetManager.GetShader("text");
	singleplayer->text = "SINGLE PLAYER";
	singleplayer->color = glm::vec3(0, 0, 0);
	singleplayer->SetAwake(true);
	world.AddEntity(singleplayer);

	Text* coop = new Text();
	coop->alias = "coop";
	coop->font = assetManager.GetFont("arial80");
	coop->shader = assetManager.GetShader("text");
	coop->text = "CO-OP";
	coop->color = glm::vec3(0, 0, 0);
	coop->SetAwake(true);
	world.AddEntity(coop);/**/

	Text* exit = new Text();
	exit->alias = "exit";
	exit->font = assetManager.GetFont("arial80");
	exit->shader = assetManager.GetShader("text");
	exit->text = "EXIT";
	exit->color = glm::vec3(0, 0, 0);
	exit->SetAwake(true);
	world.AddEntity(exit);

	/*Text* options = dynamic_cast<Text*>(exit->Copy());
	options->alias = "options";
	options->text = "OPTIONS";
	world.AddEntity(options);/**/

	Menu* mainMenu = new Menu();
	mainMenu->localTransform.position = glm::vec3(0, 300, -1);
	mainMenu->AddChild(gameTitle);
	mainMenu->AddChild(singleplayer);
	mainMenu->AddChild(coop);
	//mainMenu->AddChild(options);
	mainMenu->AddChild(exit);
	mainMenu->SetParent(camera);
	mainMenu->controller = inputManager.aggregateController;
	//mainMenu->SetAwake(false);
	world.AddEntity(mainMenu);

	Menu* pauseMenu = new Menu();
	pauseMenu->SetParent(camera);
	pauseMenu->localTransform.position = glm::vec3(0, 300, -1);
	pauseMenu->controller = inputManager.aggregateController;
	world.AddEntity(pauseMenu);

	Text* pauseText = new Text();
	pauseText->font= assetManager.GetFont("arial200");
	pauseText->shader = assetManager.GetShader("text");
	pauseText->color = glm::vec3(0, 0, 0);
	pauseText->text = "PAUSED";
	pauseText->SetParent(pauseMenu);
	world.AddEntity(pauseText);

	pauseText = dynamic_cast<Text*>(pauseText->Copy());
	pauseText->alias = "resume";
	pauseText->font = assetManager.GetFont("arial80");
	pauseText->text = "RESUME";
	pauseText->SetParent(pauseMenu);
	world.AddEntity(pauseText);

	/*pauseText = dynamic_cast<Text*>(pauseText->Copy());
	pauseText->alias = "reset";
	pauseText->font = assetManager.GetFont("arial80");
	pauseText->text = "RESET";
	pauseText->SetParent(pauseMenu);
	world.AddEntity(pauseText);*/

	pauseText = dynamic_cast<Text*>(pauseText->Copy());
	pauseText->alias = "mainMenu";
	pauseText->text = "MAIN MENU";
	pauseText->SetParent(pauseMenu);
	world.AddEntity(pauseText);

	/*pauseText = dynamic_cast<Text*>(pauseText->Copy());
	pauseText->text = "OPTIONS";
	pauseText->alias = "options";
	pauseText->SetParent(pauseMenu);
	world.AddEntity(pauseText);/**/

	pauseText = dynamic_cast<Text*>(pauseText->Copy());
	pauseText->text = "EXIT";
	pauseText->alias = "exit";
	pauseText->SetParent(pauseMenu);
	world.AddEntity(pauseText);

	pauseMenu->SetAwake(false);/**/

	Menu* gameEndMenu = new Menu();
	gameEndMenu->SetParent(camera);
	gameEndMenu->localTransform.position = glm::vec3(0, 300, -1);
	gameEndMenu->controller = inputManager.aggregateController;
	world.AddEntity(gameEndMenu);

	pauseText = dynamic_cast<Text*>(pauseText->Copy());
	pauseText->font = assetManager.GetFont("arial200");
	pauseText->text = "YOU DIED";
	pauseText->SetParent(gameEndMenu);
	world.AddEntity(pauseText);

	pauseText = dynamic_cast<Text*>(pauseText->Copy());
	pauseText->alias = "reset";
	pauseText->font = assetManager.GetFont("arial80");
	pauseText->text = "TRY AGAIN";
	pauseText->SetParent(gameEndMenu);
	world.AddEntity(pauseText);

	pauseText = dynamic_cast<Text*>(pauseText->Copy());
	pauseText->alias = "mainMenu";
	pauseText->text = "MAIN MENU";
	pauseText->SetParent(gameEndMenu);
	world.AddEntity(pauseText);

	pauseText = dynamic_cast<Text*>(pauseText->Copy());
	pauseText->alias = "exit";
	pauseText->text = "EXIT";
	pauseText->SetParent(gameEndMenu);
	world.AddEntity(pauseText);

	gameEndMenu->SetAwake(false);

	Menu* levelSelectMenu = new Menu();
	levelSelectMenu->SetParent(camera);
	levelSelectMenu->localTransform.position = glm::vec3(0, 300, -1);
	levelSelectMenu->controller = inputManager.aggregateController;
	world.AddEntity(levelSelectMenu);

	pauseText = dynamic_cast<Text*>(pauseText->Copy());
	pauseText->alias = "arena";
	pauseText->text = "LEVEL SELECT";
	pauseText->SetParent(levelSelectMenu);
	world.AddEntity(pauseText);

	pauseText = dynamic_cast<Text*>(pauseText->Copy());
	pauseText->alias = "arena";
	pauseText->text = "ARENA";
	pauseText->SetParent(levelSelectMenu);
	world.AddEntity(pauseText);

	pauseText = dynamic_cast<Text*>(pauseText->Copy());
	pauseText->alias = "back";
	pauseText->text = "BACK";
	pauseText->SetParent(levelSelectMenu);
	world.AddEntity(pauseText);

	levelSelectMenu->SetAwake(false);

	/*Menu* optionsMenu = new Menu();
	pauseMenu->SetParent(camera);
	pauseMenu->localTransform.position = glm::vec3(0, 300, -1);
	pauseMenu->controller = inputManager.aggregateController;
	world.AddEntity(pauseMenu);

	Text* menuText = new Text();
	menuText->font = assetManager.GetFont("arial200");
	menuText->shader = assetManager.GetShader("text");
	menuText->color = glm::vec3(0, 0, 0);
	menuText->text = "OPTIONS";
	menuText->SetParent(optionsMenu);
	world.AddEntity(menuText);

	menuText = dynamic_cast<Text*>(menuText->Copy());
	menuText->text = "Window Mode: Borderless Fullscreen";
	menuText->alias = "mode";
	menuText->SetParent(optionsMenu);
	world.AddEntity(menuText);/**/

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
	sceneManager->mainMenu = mainMenu;
	sceneManager->inputManager = &inputManager;
	sceneManager->pauseMenu = pauseMenu;
	sceneManager->gameOverMenu = gameEndMenu;
	sceneManager->characterSelector = charSelector;
	sceneManager->armoredEnemyMatter = assetManager.GetMaterial("armored_goblin");
	sceneManager->monsterSpawn = monsterSpawn;
	sceneManager->editor = editor;
	sceneManager->levelSelectMenu = levelSelectMenu;

	Engine engine(&world, &assetManager, &renderer);
	engine.inputManager = &inputManager;

	while (engine.GameRunning())
	{
		engine.Update();
	}

	glfwTerminate();
	
	return 0;
}

