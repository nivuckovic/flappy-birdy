#pragma once

#include <random>

class RNG {
public:
	float getFloatNumber(float a, float b);
	int getIntegerNumber(float a, float b);

	static RNG& getInstance();

private:
	RNG() {};

	// CC = delete 
	// OP = delete
};