#pragma once
#include <random>
class Random
{
public:
	std::mt19937 rng;
	std::uniform_real_distribution<double> distribution;
	double random();
	Random();
	~Random();
};

