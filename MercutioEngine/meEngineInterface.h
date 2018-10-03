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
};