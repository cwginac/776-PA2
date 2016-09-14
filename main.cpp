#include <iostream>
#include <stdlib.h>
#include <vector>
#include <time.h>

using namespace std;

// function given to us by evalX.o
double eval(int *pj);

// Helper Functions
void printArray(int* iArray);
void increment(int* iArray);
void init(int* iArray);
void copy(int* fromArray, int* toArray);

int bestArray [100];
double bestFitness = 0.0;

// Worker Function
void hillClimber();

int main()
{
	hillClimber();
	
	// Once threads are finished, print out the best array and it's fitness.
	cout << "Best Fitness: " << bestFitness << endl;
	printArray(bestArray);
}

void copy(int* fromArray, int* toArray)
{
	for(int i = 0; i < 100; i++)
	{
    	toArray[i] = fromArray[i];
 	}
}

void init(int* iArray)
{
	for(int i = 0; i < 100; i++)
	{
		iArray[i] = 0;
	}
}

void increment(int* iArray)
{
	int i = 0;
	
	while(iArray[i] == 1 && iArray[i] < 100)
	{
		i++;
	}
	
	iArray[i] = 1;
}

void printArray(int* iArray)
{
	cout << "[";
	
	for (int i = 0; i < 99; i++)
    {
        cout << iArray[i] << ",";
    }
    cout << iArray[99];
    cout << "]" << endl;
}

void hillClimber()
{
	long randomCounter = 0;
	
	// Incrementing
	double oldFitness = 0;
	int oldArray[100];
	double newFitness = 0;
	int newArray[100];
	
	while(randomCounter < 100)
	{		
		// Find a new random starting point
		init(newArray);
		oldFitness = 0;
		newFitness = eval(newArray);
		
		// While the new point is higher, keep climbing
		while(newFitness >= oldFitness)
		{
			copy(newArray, oldArray);
			oldFitness = newFitness;
			
			increment(newArray);
			newFitness = eval(newArray);			
		}
		
		// If this local maxima is better than the best known maxima, then save it off.
		if(oldFitness > bestFitness)
		{
			copy(oldArray, bestArray);
			bestFitness = oldFitness;
			cout << "New Maximum: " << oldFitness << endl;
			
			if(bestFitness == 100)
			{
				randomCounter = 100;
			}
		}
		
		randomCounter++;
	}
}
