#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
using std::cout;
using std::cin;
using std::endl;
using std::ofstream;


struct LegoProduct {
	unsigned int setNumber;
	string setTheme;
	string setName;
	unsigned int numOfMinifigs;
	unsigned int numOfParts;
	double setPrice;
};

void ReadLegoData(ifstream& dataFile, vector<LegoProduct>& LegoDataVector) {
	// Get the title information
	string buffer; 
	//The following code collects the title names on the first line. 
	getline(dataFile, buffer, ',');
	string titleNumber = buffer;
	getline(dataFile, buffer, ',');
	string titleTheme = buffer;
	getline(dataFile, buffer, ',');
	string titleName = buffer;
	getline(dataFile, buffer, ',');
	string titleMinifigs = buffer;
	getline(dataFile, buffer, ',');
	string titlePieces = buffer;
	getline(dataFile, buffer, '\n');
	string titleUSPrice = buffer;

	if (dataFile.is_open()) {
		unsigned int setNumberTemp;
		string setThemeTemp;
		string setNameTemp;
		unsigned int numOfPartsInSetTemp;
		double setPriceTemp;

		while (getline(dataFile,buffer,',')){
			LegoProduct* temp = new LegoProduct;
			cout << "buffer is " << buffer << endl;
			temp->setNumber = stoi(buffer);
			getline(dataFile, buffer, ',');
			temp->setTheme = buffer;
			getline(dataFile, buffer, ',');
			temp->setName = buffer;
			getline(dataFile, buffer, ',');
			temp->numOfMinifigs = stoi(buffer);
			getline(dataFile, buffer, ',');
			temp->numOfParts = stoi(buffer);
			getline(dataFile, buffer, '\n');
			temp->setPrice = stod(buffer);

			LegoDataVector.push_back(*temp);
		}
	}
}

int main()
{
	ifstream legoDatatInput;
	cout << std::fixed << setprecision(2);
	cout << "Which file(s) to open?\n";
	cout << "1. lego1.csv" << endl;
	cout << "2. lego2.csv" << endl;
	cout << "3. lego3.csv" << endl;
	cout << "4. All 3 files" << endl;
	int option;
	cin >> option;
	vector<LegoProduct> legoProductVectorTest;
	vector<LegoProduct> lego1;
	vector<LegoProduct> lego2;
	vector<LegoProduct> lego3;

	switch (option)
	{
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5: 
			legoDatatInput.open("test.csv");
			ReadLegoData(legoDatatInput, legoProductVectorTest);
			break;
		default:
			break;
	}

   /*======= Load data from file(s) =======*/

   
    cout << "1. Most Expensive set" << endl;
	cout << "2. Largest piece count" << endl;
	cout << "3. Search for set name containing..." << endl;
	cout << "4. Search themes..." << endl;
	cout << "5. Part count information" << endl;
	cout << "6. Price information" << endl;
	cout << "7. Minifigure information" << endl;
	cout << "8. If you bought one of everything..." << endl;
	cout << "0. Exit" << endl;
   
	int choice;
	cin >> choice;
   cin.get();  // Clear newline character for any later input
   
   /*======= Print out how many sets were loaded =======*/
   /*======= Based on the choice, execute the appropriate task and show the results =======*/
	switch (choice)
	{
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5: 
			break;
		case 6:
			break;
		case 7:
			break;
		case 8:
			break;
		case 0:
			break;
		case 9:
			for (int i = 0; i < 2; i++) {
				cout << legoProductVectorTest.at(i).setNumber;
				cout << ", "; 
				cout << legoProductVectorTest.at(i).setTheme;
				cout << ", "; 
				cout << legoProductVectorTest.at(i).setName;
				cout << ", "; 
				cout << legoProductVectorTest.at(i).numOfMinifigs;
				cout << ", "; 
				cout << legoProductVectorTest.at(i).numOfParts;
				cout << ", "; 
				cout << legoProductVectorTest.at(i).setPrice;
				cout << endl;
			}
			break;
		default:
			break;
	}
   
	return 0;
}


