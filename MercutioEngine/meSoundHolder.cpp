#include "stdafx.h"
#include "meSoundHolder.h"

void SoundHolder::Play(std::string str)
{
	int index = RandInt(0, holders[str]->size() - 1);
	if (holders[str]->at(index)->getBuffer() != NULL)
	{
		holders[str]->at(index)->play();
	}/**/
}

void SoundHolder::LoadSounds(std::string manifest)
{
	std::fstream file;
	std::string line;
	std::vector<std::string> parsedLine;
	file.open(manifest.c_str());
	std::string lastHolder = "";
	if (!file.is_open())
	{
		std::cout << "File " << manifest << " failed to open.\n";
		return;
	}
	while (std::getline(file, line))
	{
		Parser(line, parsedLine);
		if (parsedLine[0][0] == '/') { continue; }
		//std::vector<sf::Sound> *newHolder;
		
		if (parsedLine[0] == "#Holder")
		{
			holders[parsedLine[1]] = new std::vector<sf::Sound*>();
			//std::cout << parsedLine[1] << "\n";
			lastHolder = parsedLine[1];
		}
		else
		{
			buffers.push_back(new sf::SoundBuffer);
			//std::cout << lastHolder << "\n";
			//std::cout << holders.count(lastHolder) << "\n";
			holders[lastHolder]->push_back(new sf::Sound);
			//std::cout << parsedLine[0] << "\n";
			(buffers.back())->loadFromFile(parsedLine[0]);
			//std::cout << parsedLine[0] << "\n";
			holders[lastHolder]->back()->setBuffer(*buffers.back());
		}
	}
	/*for (std::map<std::string, std::vector<sf::Sound*>*>::iterator it = holders.begin(); it != holders.end(); ++it)
	{
		std::cout << it->first << "\n";
	}/**/
}

SoundHolder::SoundHolder(){}
SoundHolder::~SoundHolder()
{
	for (size_t i = 0; i < buffers.size(); i++)
	{
		delete buffers[i];
	}
	for (std::map<std::string, std::vector<sf::Sound*>*>::iterator it = holders.begin(); it != holders.end(); ++it)
	{
		for (size_t i = 0; i < it->second->size(); i++)
		{
			delete it->second->at(i);
		}
		delete it->second;
	}
	/*
	for (std::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';
	/**/
}