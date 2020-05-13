#include "Random.h"


Random::Random() {
}



bool Random::nextBool() {
	return nextInt(2) == 0;
}

unsigned int Random::nextInt() {
	return std::rand();
}


unsigned int Random::nextInt(unsigned int n) {
	return nextInt() % n;
}


unsigned int Random::operator() () {
	return nextInt();
}


unsigned int Random::operator() (int n) {
	return nextInt(n);
}

/**
 * @return a random float in [0..1)
 */
float Random::nextFloat() {
	return (float)nextInt() / (float)getRandMax();
}


double Random::nextDouble() {
	return (double)nextInt() / (double)getRandMax();
}


unsigned int Random::getRandMax() {
	return RAND_MAX;
}


void Random::setSeed(unsigned int seed) {
	std::srand(seed);
}


void Random::initSeed() {
	setSeed((unsigned)std::time(nullptr));
}