#pragma once

#include "meEntity.h"
#include <SFML\Audio.hpp>
#include "meProjectile.h"
#include "meInput.h"

class Actor : public Entity
{
public:
	float speed = 700.0f;
	float projectileSpeed = 800.0f;
	int health = 3;
	int maxHealth = 3;
	bool alive = true;
	float invulnTime = 1.0f;
	float invulnClock = 0.0f;
	bool isDodging = false;
	float dodgeTime = 0.3f;
	float moveLockTime = 0.5f;
	float moveLockClock = 0.0f;
	float dodgeSpeed = speed * 2.5f;
	float teleportDistance = 400.0f;

	float charge = 0.0f;
	float chargeRate = 1.0f;
	float chargeDrain = 1.0f;
	float maxCharge = 1.0f;
	float minCharge = 0.1f;
	float launchCharge = 0.0f;
	float chargeDeadzone = 0.8f;
	float chopstickSpacing = 15.0f;
	float itemOffset = 100.0f;

	int numProjectiles = 1;
	int numBonusProjectiles = 0;
	int numCurrentProjectiles = 0;
	float spread = 60.0f;
	bool canFire = true;
	bool canMove = true;
	bool canChangeCourse = true;
	float chargeRateMult = 1.0f;
	float projectileSpeedMult = 1.0f;
	bool projectilesParallel = true;
	bool instantCharge = false;

	Material* redMatter;
	Material* tedMatter;
	Material* keyMatter;
	Material* tanMatter;
	Material* ninjaMatter;
	Material* lastMatter;

	const int maxProjectiles = 5;
	const int numBelts = 5;

	Entity* wok;
	Entity* spoon;
	Entity* chopstick;
	Entity* roller;
	Entity* wave;

	/*struct Characters
	{
		enum Character
		{
			red,
			ted,
			tan,
			key,
			none
		};
	};*/

	struct Weapons
	{
		enum Weapon
		{
			wok,
			spoon,
			chopstick,
			roller,
			none,
		};
	};

	struct Dashes
	{
		enum Dash
		{
			normal,
			speed,
			damage,
			teleport,
			none
		};
	};

	enum Character
	{
		red,
		ted,
		tan,
		key,
		none
	};

	enum Dash
	{
		_normal,
		_speed,
		_damage,
		_teleport,
		_none
	};

	enum State
	{
		charging,
		dashing,
	};

	Weapons::Weapon weapon = Weapons::wok;
	Dashes::Dash dash = Dashes::normal;
	//Characters::Character character = Characters::red;
	Character character = red;

	InputController* controller;
	sf::Sound shootSound;

	glm::vec2 chargeVec;

	void SetBelts(bool spawn = true);

	void SetCharacter(Character newChar);
	//void SetCharacter(Characters::Character newChar);
	void SetWeapon(Weapons::Weapon newWeapon);
	void SetWeapon(Entity* newWeapon);
	void SetDash(Dashes::Dash newDash);

	void Damage();

	Actor();

	Entity* Copy();

	void Update();
	void OnCollision(Entity* ent);
	void ManageProjectiles();
	void ManageDash();
};