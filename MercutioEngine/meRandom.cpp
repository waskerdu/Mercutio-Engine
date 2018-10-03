#include "stdafx.h"
#include "meRandom.h"
#include <chrono>

Random::Random()
{
	rng.seed((unsigned int)std::chrono::system_clock::now().time_since_epoch().count());
	distribution = std::uniform_real_distribution<double>(0.0, 1.0);
}

Random::~Random()
{
}

double Random::random()
{
	return distribution(rng);
}
