#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <thread>
#include <vector>
#include <time.h>

#define __DEBUG__

using namespace std;

double eval(int *pj);

void generatePopulation();
void evaluatePopulation();
void selectPopulation();
void crossoverPopulation();
void mutatePopulation();

int getWeightedPosition();

const int populationSize = 100;
const int chromosomes = 150;
const int maxGen = 100000;

vector<vector<int>> currentPopulation;
vector<vector<int>> newPopulation;
vector<double> weights;

vector<int> fittest;
int fittestFitness = 0;

int main()
{
	int currentGeneration = 0;
	
	generatePopulation();
	evaluatePopulation();
	
	while(currentGeneration < maxGen)
	{
		cout << "Current Generation: " << currentGeneration << endl;
		selectPopulation();
		crossoverPopulation();
		mutatePopulation();
		
		currentPopulation = newPopulation;
		evaluatePopulation();
		currentGeneration++;
	}
	return 0;
}

void generatePopulation()
{
	srand(1);
	
	vector<int> member;
	for(int i = 0; i < populationSize; i++)
	{	
		member.clear();
		for(int c = 0; c < chromosomes; c++)
		{
			member.push_back(rand() % 2);
		}
		currentPopulation.push_back(member);
	}
}

void evaluatePopulation()
{
	weights.clear();
	double fitness = 0;
	
	int population[150];
	std::copy(currentPopulation[0].begin(), currentPopulation[0].end(), population);
	fitness = eval(population);
	weights.push_back(fitness);
	
	if(fitness > fittestFitness)
	{
		fittest = currentPopulation[0];
		fittestFitness = fitness;
	}
	
	for(int i = 1; i < populationSize; i++)
	{
		std::copy(currentPopulation[i].begin(), currentPopulation[i].end(), population);
		
		fitness = eval(population);
		weights.push_back(fitness + weights[i-1]);
	
		if(fitness > fittestFitness)
		{
			fittest = currentPopulation[0];
			fittestFitness = fitness;
		}
	}
	
	#ifdef __DEBUG__
	double averageFitness = weights[populationSize -1] / (double)populationSize;
	cout << "Current Fittest: " << fittestFitness << endl;
	cout << "Average Fitness: " << averageFitness << endl;
	#endif
}

void selectPopulation()
{
	newPopulation.clear();
	int selectedMember = -1;
	
	for(int i = 0; i < populationSize; i++)
	{
		selectedMember = getWeightedPosition();
		newPopulation.push_back(currentPopulation[selectedMember]);
	}
}

int getWeightedPosition()
{
	int totalWeight = weights[populationSize - 1];
	
	int rng = rand() % totalWeight;
	
	for(int i = 0; i < populationSize; i++)
	{
		if(rng < weights[i])
		{
			return i;
		}
	}
}

void crossoverPopulation()
{
	int crossoverRNG = -1;
	int positionRNG = -1;
	
	int i = 0;
	
	while(i < populationSize)
	{
		vector<int> parent1 = newPopulation[i];
		vector<int> parent2 = newPopulation[i+1];
		
		crossoverRNG = rand() % 100;
		
		if(crossoverRNG < 70)
		{
			positionRNG = rand() % chromosomes;
			
			for(int c = 0; c < chromosomes; c++)
			{
				if(c >= positionRNG)
				{
					newPopulation[i][c] = parent2[c];
					newPopulation[i+1][c] = parent1[c];
				}
			}
		}	
		
		i += 2;	
	}
}

void mutatePopulation()
{
	int mutationRNG  = -1;
	for(int i = 0; i < populationSize; i++)
	{
		for(int c = 0; c < chromosomes; c++)
		{
			mutationRNG = rand() % 1000 + 1;
			
			if(mutationRNG == 1)
			{
				newPopulation[i][c] = !newPopulation[i][c];
			}
		}
	}
}	
