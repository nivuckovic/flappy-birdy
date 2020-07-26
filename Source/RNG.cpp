#include "RNG.h"
#include "..\Include\RNG.h"

float RNG::getFloatNumber(float a, float b) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(a, b);

	return dis(gen);
}

int RNG::getIntegerNumber(float a, float b) {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(a, b);

	return dis(gen);
}

RNG& RNG::getInstance() {
	static RNG instance;

	return instance;
}
