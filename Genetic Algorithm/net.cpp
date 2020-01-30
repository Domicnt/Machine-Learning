#include "stdafx.h"

Net::Net(std::vector<int> const Amount)
{
	fitness = 0;

	amount = Amount;
	
	for (auto i = 0; i < std::size(amount); i++)
	{
		neurons.emplace_back();
		biases.emplace_back();
		for (auto j = 0; j < amount[i]; j++)
		{
			neurons[i].push_back(0);
			biases[i].push_back(0);
		}
	}

	for (auto i = 1; i < std::size(neurons); i++)
	{
		weights.emplace_back();
		for (auto j = 0; j < std::size(neurons[i]); j++)
		{
			weights[i-1].emplace_back();
			for (auto k = 0; k < std::size(neurons[i - 1]); k++)
			{
				weights[i-1][j].push_back(0);
			}
		}
	}
}

double Net::sigmoid(const double x)
{
	const auto e = 2.71828;
	return 1. / (1 + pow(e, -x));
}

void Net::calculate()
{
	for (unsigned int i = 1; i < std::size(neurons); i++)
	{
		for (unsigned int j = 0; j < std::size(neurons[i]); j++)
		{
			double sum = 0;
			for (auto k = 0; k < std::size(neurons[i - 1]); k++)
			{
				sum += neurons[i - 1][k] * weights[i - 1][j][k];
			}
			neurons[i][j] = sigmoid(sum) + biases[i][j];
		}
	}
}

void Net::mutate(int mutations)
{
	for (auto mutated = 0; mutated < mutations; mutated++) 
	{
		if (rand() % 10 < 9) {
			auto const i = rand() % std::size(weights);
			auto const j = rand() % std::size(weights[i]);
			auto const k = rand() % std::size(weights[i][j]);

			weights[i][j][k] += double(rand() % 200 - 100.) / 100;
		}
		else
		{
			auto const i = rand() % std::size(biases);
			auto const j = rand() % std::size(biases[i]);

			biases[i][j] += double(rand() % 200 - 100.) / 5000;
		}
	}
}

Net Net::cross(Net b)
{
	Net net(amount);
	for(auto i = 0; i < std::size(weights); i++)
	{
		for (auto j = 0; j < std::size(weights[i]); j++)
		{
			for (auto k = 0; k < std::size(weights[i][j]); k++)
			{
				net.weights[i][j][k] = rand() % 2 ? weights[i][j][k] : b.weights[i][j][k];
			}
		}
	}
	for (auto i = 0; i < std::size(biases); i++)
	{
		for (auto j = 0; j < std::size(biases[i]); j++)
		{
			net.biases[i][j] = rand() % 2 ? biases[i][j] : b.biases[i][j];
		}
	}
	return net;
}


void Net::drawNet(SDLWrapper &sdl, const SDL_Rect dstRect)
{
	const int segments = std::size(neurons);
	auto vertSegments = 0;
	for(auto i : neurons)
	{
		if (std::size(i) > vertSegments)
			vertSegments = std::size(i);
	}
	const auto spacing = dstRect.w / segments;

	const int size = spacing < dstRect.h / vertSegments ? spacing / 2 : dstRect.h / vertSegments / 2;//0
	
	std::vector<std::vector<SDL_Rect>> rects;
	std::vector<std::vector<double>> nums;
	
	rects.emplace_back();
	nums.emplace_back();
	
	for (auto i = 0; i < segments; i++)
	{
		rects.emplace_back();
		nums.emplace_back();
		int x = dstRect.x + i * spacing + spacing / 2;
		for (auto j = 0; j < std::size(neurons[i]); j++)
		{
			int y = dstRect.y + dstRect.h / (std::size(neurons[i]) + 1) * (j + 1);
			rects[i + 1].push_back({x - size/2, y - size/2, size, size});
			nums[i + 1].push_back(neurons[i][j]);
		}
	}

	//set up sdl ttf
	const SDL_Color textColor = { 0, 0, 0 };
	auto font = TTF_OpenFont("../Assets/Fonts/sans.ttf", 60);
	
	for (auto i = 0; i < std::size(rects); i++)
	{
		for (auto j = 0; j < std::size(rects[i]); j++)
		{
			if (i + 1 < std::size(rects)) {
				for (auto k : rects[i + 1])
				{
					SDL_RenderDrawLine(sdl.renderer, rects[i][j].x + rects[i][j].w/2, rects[i][j].y + rects[i][j].h/2, k.x + k.w/2, k.y + k.h/2);
				}
			}
			SDL_RenderFillRect(sdl.renderer, &rects[i][j]);
			
			const float number = nums[i][j];

			char cha[255];
			sprintf_s(cha, "%f", number);
			
			auto const message = TTF_RenderText_Blended(font, cha, textColor);

			sdl.renderSurface(message, rects[i][j]);
		}
	}
	TTF_CloseFont(font);
}