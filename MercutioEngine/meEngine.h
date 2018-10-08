#pragma once
#include "meRender.h"
#include <string>
#include "meWorld.h"
#include "meTime.h"
#include "meAssetManager.h"
#include "meText.h"
#include "meRandom.h"
#include "meInput.h"
#include "meMonitorMode.h"

class Engine
{
	std::string MercutioVersion = "Mercutio 0.1.0";
	bool gameRunning = true;
	bool needsInit = true;
	bool needsReset = false;
	bool isPaused = false;
	World* worldPtr;
	AssetManager* assetManagerPtr;
	double lastTime = 0;
	double time;
	double deltaTime;
	double deltaTimeCo = 1;
	double timeCo = 1;
	double deltaTimeCoClock = 0;
	double fixedTime = 1.0 / 30.0;
	double fixedTimer = 0;
	bool toggle = false;
	Random* random;
	bool resetButtonState = false;
	MonitorMode windowedMonitorMode;
	MonitorMode borderlessMonitorMode;
	MonitorMode fullscreenMonitorMode;
	MonitorMode* tempMonitorMode;
	MonitorMode currentMonitorMode;
	bool confirmOptions = false;
	bool modeChanged = false;
	MonitorMode::WindowMode windowMode = MonitorMode::borderlessFullscreen;
	GLFWwindow* window;
	int numMonitors;
	GLFWmonitor** monitors;
	//int vsync = 1;
public:
	Renderer* renderPtr;
	bool resizedLastFrame = false;
	InputManager* inputManager;
private:
	void Init();
	void PhysicsUpdate();
public:
	bool GameRunning();
	bool NeedsInit();
	Engine(World* worldPtr, AssetManager* assetManagerPtr, Renderer* renderPtr);
	~Engine();
	void EntityUpdate();
	void UpdateHelper(Entity* ent);
	void FixedUpdate();
	void Update();
	void Reset();
	void ConfirmOptions();
	void ChangeMode();
};