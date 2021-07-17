#include <iostream>
#include <map>
#include <random>
#include <ctime>
using namespace std;

mt19937 random_mt;

int Random(int min, int max)
{
	uniform_int_distribution<int> dist(min, max);
	return dist(random_mt);
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
		cout << "Random seed value: ";
		cin >> randomSeed;
		random_mt.seed(randomSeed);


		cout << "Number of times to roll the die: ";
      // user input

		cout << "Number of sides on this die: ";
      // user input

		// Roll Dice
	}
	else if (option == 2)
	{
	   // Load the states
	   
	   // Get input for option 1 (show all states) or 2 (do a search for a particular state)

	}

	return 0;
}
