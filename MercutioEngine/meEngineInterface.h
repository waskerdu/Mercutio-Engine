#pragma once
#include "meEntity.h"
struct EngineInterface
{
	static double GetDeltaTimeCo(Entity* ent) { return *(ent->deltaTimeCo); }
	static void SetDeltaTimeCo(Entity* ent, double deltaTimeCo) { *(ent->deltaTimeCo) = deltaTimeCo; }
	static void SetDeltaTimeCoClock(Entity* ent, double deltaTimeCoClock) { *(ent->deltaTimeCoClock) = deltaTimeCoClock; }
	static void Reset(Entity* ent) { *(ent->needsReset) = true; }
	static void Quit(Entity* ent){ *(ent->gameRunning) = false; }
	static void Pause(Entity* ent, bool pause) { *(ent->isPaused) = pause; }
	static bool IsPaused(Entity* ent) { return *(ent->isPaused); }
	static void SetResolution(Entity* ent, int width, int height) 
	{
		MonitorMode* temp = *ent->tempMonitorMode;
		temp->windowWidth = width;
		temp->viewWidth = width;
		temp->windowHeight = height;
		temp->viewHeight = height;
	}
	static void SetMode(Entity* ent, MonitorMode::WindowMode mode) 
	{
		*ent->windowMode = mode;
		*ent->modeChanged = true;
	}
	static void SetVsync(Entity* ent, int vsync) { (*ent->tempMonitorMode)->vsync = vsync; }
	static int GetVsync(Entity* ent) { return (*ent->tempMonitorMode)->vsync; }
	//static void SetFramerateCap(Entity* ent, int cap) { ent->monitorMode->framerateCap = cap; }
	static void OptionsConfirm(Entity* ent) { *ent->optionsConfirm = true; }
	static MonitorMode::WindowMode GetWindowMode(Entity* ent) { return (*ent->tempMonitorMode)->windowMode; }
	static int GetNumberOfMonitors(Entity* ent) { return *ent->numMonitors; }
	static MonitorMode* GetMonitorMode(Entity* ent) { return *ent->tempMonitorMode; }
	static void SetCurrentMonitor(Entity* ent, int num) 
	{ 
		(*ent->tempMonitorMode)->monitorIndex = num; 
		(*ent->tempMonitorMode)->monitorChanged = true;
	}
	static const GLFWvidmode* GetSupportedResolutions(Entity* ent, int* numSupported)
	{
		//
		*numSupported = *ent->numSupportedResolutions;
		return *ent->supportedResolutions;
	}
	static void SetVideoMode(Entity* ent, const GLFWvidmode* mode)
	{
		MonitorMode* temp = *ent->tempMonitorMode;
		temp->videoMode = mode;
		temp->windowWidth = mode->width;
		temp->viewWidth = mode->width;
		temp->windowHeight = mode->height;
		temp->viewHeight = mode->height;
		temp->framerateCap = mode->refreshRate;
	}
	static const GLFWvidmode* GetVideoMode(Entity* ent)
	{
		return (*ent->tempMonitorMode)->videoMode;
	}
};