#include "stdafx.h"

Genetic::Genetic(int MaxGen)
{
	nets = 100;
	for (auto i = 0; i < nets; i++)
	{
		population.push_back({ {2, 1} });
	}
	maxGen = MaxGen;
	gen = 0;
}

void Genetic::run(Game game)
{
	for (gen = 0;  gen < maxGen; gen++) {
		printf("generation %d\n", gen + 1);

		for (auto j = 0; j < nets; j++)
		{
			if (gen == 0) 
				threads.push_back(game.thread(population[j], 100));
			else 
				threads[j] = game.thread(population[j], 100);
		}
		for (auto j = 0; j < nets; j++)
		{
			threads[j].join();
		}
		if(gen == maxGen - 1)
			threads.clear();

		std::sort(population.begin(), population.end(), [](Net const& a, Net const& b) -> bool { return a.fitness > b.fitness; });
		best = population[0];

		//get best and average fitness
		bestFitness.push_back(population[0].fitness);

		printf("Fitness: %f; Total improvement: %f\n", bestFitness[gen], bestFitness[gen] - bestFitness[0]);

		//elitism
		std::vector<Net> elites;

		for(auto j = 0; j < nets / 10; j++)
		{
			elites.push_back(population[j]);
		}
		
		//parent population
		std::vector<Net> population2;
		
		//fill parent population
		for (auto j = nets/10; j < nets;)
		{
			auto r = rand() % nets / 2;//cull worse half
			if (fmod(rand(), population[r].fitness) < population[0].fitness / population[r].fitness)
			{
				population2.push_back(population[r]);
				j++;
			}
		}

		population.clear();

		//keep elites
		for (auto j = 0; j < nets / 10; j++)
		{
			population.push_back(elites[j]);
		}

		//fill population with children
		for (auto j = nets / 10; j < nets; j++)
		{
			population.push_back(population2[j - nets / 10].cross(population2[rand() % (nets - nets / 10)]));
			population[j].mutate(rand() % 3 + 1);
			if(rand() % 500 == 1)
				population[j].mutate(500);//large mutation every once in a while
		}
	}
}