#pragma once
#include <random>

class Random
{
	static std::mt19937 random;
public:
	// One instance of x, all instances share this variable
	static int x;
	static int Int(int min, int max);
	static float Float(float min, float max);
};

