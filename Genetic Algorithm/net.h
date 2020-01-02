#pragma once
#include "stdafx.h"

class Net
{
public:
	//neurons
	std::vector<std::vector<double>> neurons;
	std::vector<std::vector<double>> biases;

	//synapses
	std::vector<std::vector<std::vector<double>>> weights;

	std::vector<int> amount;

	float fitness;

	Net() {}
	Net(std::vector<int> Amount);

	double sigmoid(double x);
	double sigmoidnt(double x);

	void calculate();

	void mutate(int mutations);
	Net cross(Net b);
	

	void drawNet(SDLWrapper &sdl, const SDL_Rect dstRect);
};