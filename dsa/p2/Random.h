#pragma once
#include <random>
#include <ctime>

class Random
{
	static std::mt19937 random;
public:
	// One instance of x, all instances share this variable
	static int x;
	static int Int(int min, int max);
};

// Static variables must be redeclared in global space
std::mt19937 Random::random(time(0));
int Random::x = 100;

int Random::Int(int min, int max)
{
	std::uniform_int_distribution<int> dist(min, max);

	return dist(random);
}