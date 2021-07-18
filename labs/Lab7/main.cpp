#include <iostream>
#include <map>
#include <random>
#include <ctime>
using namespace std;
using std::map;

mt19937 random_mt;

int Random(int min, int max)
{
	uniform_int_distribution<int> dist(min, max);
	return dist(random_mt);
}

void RollDice(int numberOfRolls, int numberOfSides) {
	map<int, int> rollResults;
	map<int, int>::iterator iter = rollResults.begin();
	map<int, string> myMap;

	// Seed the map
	for (int i = 0; i <= numberOfSides; i++) {
		rollResults[i] = 0; 
	}

	for (int i = 0; i < numberOfRolls; i++) {
		rollResults[Random(1, numberOfSides)]++;
	}

	for (; iter != rollResults.end(); ++iter) {
		cout << "key is: " << iter->first;
		cout << "Value is: " << iter->second;
	}

	
}

int main()
{
	cout << "1. Random Numbers\n";
	cout << "2. State Info\n";

	int option;
	cin >> option;

	if (option == 1)
	{
		int randomSeed;
		int numOfRolls;
		int numOfSides;

		cout << "Random seed value: ";
		cin >> randomSeed;
		random_mt.seed(randomSeed);


		cout << "Number of times to roll the die: ";
      // user input
	  	cin >> numOfRolls;

		cout << "Number of sides on this die: ";
      // user input
	  	cin >> numOfSides;

		// Roll Dice
		void RollDice(int numOfRolls, int numOfSides); 
	}
	else if (option == 2)
	{
	   // Load the states
	   
	   // Get input for option 1 (show all states) or 2 (do a search for a particular state)

	}

	return 0;
}
