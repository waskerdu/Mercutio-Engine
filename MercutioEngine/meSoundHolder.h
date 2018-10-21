#pragma once

#include <vector>
#include <map>
#include <SFML\Audio.hpp>
#include <iostream>
#include "meEntity.h"
#include "meParser.h"
#include <fstream>

class SoundHolder : public Entity
{
public:
	std::vector<sf::SoundBuffer*> buffers;
	std::map<std::string, std::vector<sf::Sound*>*> holders;
	void Play(std::string str);
	void LoadSounds(std::string manifest);

	SoundHolder::SoundHolder();
	SoundHolder::~SoundHolder();
};