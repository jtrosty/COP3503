#include <iostream>
#include <map>
#include <random>
#include <ctime>
#include <fstream>
#include <string>
using namespace std;
using std::map;
using std::ifstream;
using std::stoi;

mt19937 random_mt;

class StateData {
	public:
		string name;
		int perCapitaIncome;
		int population;
		int medianHoueholdIncome;
		int numOfHouseholds;

		void printStatesData();
};

void StateData::printStatesData() {
	cout << name << endl;
	cout << "Population: " << population << endl;
	cout << "Per Capita Income: " << perCapitaIncome << endl;
	cout << "Median Household Income: " << medianHoueholdIncome << endl;
	cout << "Number of Households: " << numOfHouseholds << endl;
}

// Prototypes
void RollDice(int numberOfRolls, int numberOfSides);

int Random(int min, int max)
{
	uniform_int_distribution<int> dist(min, max);
	return dist(random_mt);
}

// Rolls dice and displays the result
void RollDice(int numberOfRolls, int numberOfSides) {
	map<int, int> rollResults;
	map<int, int>::iterator iter;

	// Seed the map
	for (int i = 1; i <= numberOfSides; i++) {
		rollResults.emplace(i, 0); 
	}

	for (int i = 0; i < numberOfRolls; i++) {
		rollResults.at(Random(1, numberOfSides))++;
	}

	cout << endl;
	for (iter = rollResults.begin(); iter != rollResults.end(); ++iter) {
		cout << iter->first << ": ";
		cout << iter->second << endl;
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
		RollDice(numOfRolls, numOfSides); 
	}
	else if (option == 2)
	{
		ifstream inputData;
		inputData.open("states.csv");
		map<string, StateData> states;
		map<string, StateData>::iterator iter;
		string tempLine;

		// Load the states
		if (inputData.is_open()) {
			// Get passed header data
			// Data looks like this
			// line 1
			// State, Per capita income, Population,Median Household income, Number of households
			// NOTE NO COMMA AT THE END.
			// line 2
			// Mississippi, 21036, 2994079, 39680, 1095823 

				// bypass header data
			getline(inputData, tempLine); // Sate
			/*
			getline(inputData, tempLine, ','); // Per capita income
			getline(inputData, tempLine, ','); // population
			getline(inputData, tempLine, ','); // Median HH income
			getline(inputData, tempLine); // Num of HH
			*/


			while (getline(inputData, tempLine, ',')) {
				//cout << tempLine << endl;
				StateData tempState;
				tempState.name = tempLine;
				getline(inputData, tempLine, ',');
				tempState.perCapitaIncome = stoi(tempLine);
				getline(inputData, tempLine, ',');
				tempState.population = stoi(tempLine);
				getline(inputData, tempLine, ',');
				tempState.medianHoueholdIncome = stoi(tempLine);
				getline(inputData, tempLine, '\n');
				tempState.numOfHouseholds = stoi(tempLine);
				states.emplace(tempState.name, tempState);
			}
		}
	   
		// Get input for option 1 (show all states) or 2 (do a search for a particular state)
		cout << "1. Print all states" << endl;
		cout << "2. Search for a state" << endl;
		int choice;
		cin >> choice;
		if (choice == 1) {
				for (iter = states.begin(); iter != states.end(); iter++) {
					iter->second.printStatesData();
				}
		}
		else if (choice == 2) {
			string stateChoice;
			cin >> stateChoice;
			iter = states.find(stateChoice);
			if (states.count(stateChoice) == 1) {
				iter->second.printStatesData();
			}
			else {
				cout << "No match found for " << stateChoice << endl;
			}
		}
	}

	return 0;
}
