#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <map>
#include "Color.h"
using namespace std;

void ReadFile(const char* filename,  map<string, Color>& colors);
void PrintColors(const map<string, Color>& colors);
void PrintColor(const Color& color);
void SearchForColor(map<string, Color>& colors);

int main()
{


	cout << "1-6: Load colors1/2/3/4/5/6.txt" << endl;
	cout << "7. Load all 6 files" << endl;
	int choice;
	cin >> choice;

	map<string, Color> colors;
	colors.begin();
	if (choice >= 1 && choice <= 6)
	{
		string file = "colors" + to_string(choice) + ".txt";
		ReadFile(file.c_str(), colors);
	}
	else if (choice == 7)
	{
		for (int i = 1; i <= 6; i++)
		{
			string file = "colors" + to_string(i) + ".txt";
			ReadFile(file.c_str(), colors);
		}

	}
	
	// Secondary menu
	cout << "1. Show all colors" << endl;
	cout << "2. Search for a color" << endl;
	cin >> choice;

	if (choice == 1)
		PrintColors(colors);
	else if (choice == 2)
		SearchForColor(colors);
	return 0;
}

void ReadFile(const char* filename, map<string, Color>& colors)
{
   // TODO: Read the file, create and store some Color objects
   ifstream file(filename);
   string tempColorName;
   char* tempsChar;
   string tempColorValueStr;
   int tempColorValue;
   int lengthOfString;

   while (getline(file, tempColorName, ' ')) {
	   	// Get the string value and convert to char*
		lengthOfString = tempColorName.size();
		tempsChar = new char[lengthOfString + 1];
		for (int i = 0; i < lengthOfString; i++) {
			tempsChar[i] = tempColorName.at(i);
		}
		tempsChar[lengthOfString] = '\0';

		// Get the Int value
		getline(file, tempColorValueStr, '\n');
		tempColorValue = stoi(tempColorValueStr);

		// Make a new color
		Color tempColor(tempsChar, tempColorValue);
	    colors.emplace(tempColorName, tempColor);

		//cout << tempsChar << " " << tempColorValue << endl;

	   delete tempsChar;
   }
}

void PrintColors(const map<string, Color>& colors)
{
   // Print out the color count afterward
   map<string, Color>::const_iterator iter = colors.begin();
   for (; iter != colors.end(); ++iter) {
	   PrintColor(iter->second);
   }
   cout << "Number of colors: " << colors.size();
}

void PrintColor(const Color& color)
{
	cout << left << setw(20) << color.GetName();
	cout << right << setw(10) << color.GetHexValue();
	cout << "\t\t" << (int)color.GetR() << "," << (int)color.GetG() << "," << (int)color.GetB() << endl;
}
void SearchForColor(map<string, Color>& colors)
{
	// Get some input, check if that key exists, then print out the color (or an error message)
	string userInput;
	cin >> userInput;

	if (colors.find(userInput) != colors.end()) {
		PrintColor(colors.find(userInput)->second);
	}
	else {
		cout << userInput << " not found!" << endl;
	}
}
