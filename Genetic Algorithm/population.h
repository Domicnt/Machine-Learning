#pragma once
#include "stdafx.h"

class Genetic
{
public:
	int nets;//size of population
	std::vector<Net> population;
	Net best;

	//multithreading
	std::vector<std::thread> threads;

	int maxGen;
	int gen;
	
	std::vector<float> bestFitness;//every generation
	
	Genetic(int MaxGen);
	void run(Game game);
};