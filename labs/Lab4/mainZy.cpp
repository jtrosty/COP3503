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
	unsigned int numberID;
	string theme;
	string name;
	unsigned int numOfMinifigs;
	unsigned int numOfPieces;
	double price;
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
		unsigned int numOfPiecesInSetTemp;
		double setPriceTemp;

		while (getline(dataFile,buffer,',')){
			LegoProduct* temp = new LegoProduct;
			//cout << "buffer is " << buffer << endl; TODO remove
			temp->numberID = stoi(buffer);
			getline(dataFile, buffer, ',');
			temp->theme = buffer;
			getline(dataFile, buffer, ',');
			temp->name = buffer;
			getline(dataFile, buffer, ',');
			temp->numOfMinifigs = stoi(buffer);
			getline(dataFile, buffer, ',');
			temp->numOfPieces = stoi(buffer);
			getline(dataFile, buffer, '\n');
			temp->price = stod(buffer);

			LegoDataVector.push_back(*temp);
		}
	}
}

void PrintNumOfDataRecorded(vector<vector <LegoProduct> >& data) {
    int sumOfDataRecorded = 0;
    for (int i = 0; i < data.size(); i++) {
        sumOfDataRecorded += data.at(i).size(); 
    }
    cout << "Datat collected: " << sumOfDataRecorded << endl;
}

void MostExpensiveProdcut(vector<vector <LegoProduct> >& data) {
    int mostExpenseiveSet = 0;
    int collectionWithMostExpensiveSet = 0;
    int numOfCollections = data.size();
    int numOfSets = 0;
    for (int collection = 0; collection < numOfCollections; collection++) {
        numOfSets = data.at(collection).size();
        cout << "Num of Sets " << numOfSets << endl;
        for (int set = 0; set < numOfSets; set++) {
            if (data.at(collection).at(set).price > data.at(collectionWithMostExpensiveSet).at(mostExpenseiveSet).price) {
                mostExpenseiveSet = set;
                collectionWithMostExpensiveSet = collection;
            } 
        }
    }
    cout << "The most expensive set is: " << endl;
    cout << "Name: " << data.at(collectionWithMostExpensiveSet).at(mostExpenseiveSet).name << endl;
    cout << "Number: " << data.at(collectionWithMostExpensiveSet).at(mostExpenseiveSet).numberID << endl;
    cout << "Theme: " << data.at(collectionWithMostExpensiveSet).at(mostExpenseiveSet).theme << endl;
}

void LargestPieceCount(vector<vector <LegoProduct> >& data) {
    int largestPieceCountSet = 0;
    int collectionWithSetWithLargePieceCount = 0;
    int numOfCollections = data.size();
    int numOfSets = 0;
    for (int collection = 0; collection < numOfCollections; collection++) {
        numOfSets = data.at(collection).size();
        cout << "Num of Sets " << numOfSets << endl;
        for (int set = 0; set < numOfSets; set++) {
            if (data.at(collection).at(set).numOfPieces > data.at(collectionWithSetWithLargePieceCount).at(largestPieceCountSet).numOfPieces) {
                largestPieceCountSet = set;
                collectionWithSetWithLargePieceCount = collection;
            } 
        }
    }
    cout << "The most expensive set is: " << endl;
    cout << "Name: " << data.at(collectionWithSetWithLargePieceCount).at(largestPieceCountSet).name << endl;
    cout << "Number: " << data.at(collectionWithSetWithLargePieceCount).at(largestPieceCountSet).numberID << endl;
    cout << "Theme: " << data.at(collectionWithSetWithLargePieceCount).at(largestPieceCountSet).theme << endl;
    cout << "Price: $" << data.at(collectionWithSetWithLargePieceCount).at(largestPieceCountSet).price << endl;
    cout << "Minifigures: " << data.at(collectionWithSetWithLargePieceCount).at(largestPieceCountSet).numOfMinifigs << endl;
    cout << "Theme: " << data.at(collectionWithSetWithLargePieceCount).at(largestPieceCountSet).numOfPieces << endl;
}

void NameSearch(vector<vector <LegoProduct> >& data) {
    int numOfCollections = data.size();
    bool nameFound = false;
    int numOfSets = 0;
    vector<int> result;

    string searchTerm;
    cin >> searchTerm;
    cin.get();

    for (int collection = 0; collection < numOfCollections; collection++) {
        numOfSets = data.at(collection).size();
        cout << "Num of Sets " << numOfSets << endl;
        for (int set = 0; set < numOfSets; set++) {
            if (data.at(collection).at(set).name.find(searchTerm) != string::npos) {
                nameFound = true;
                result.push_back(collection);
                result.push_back(set);
            } 
        }
    }
    if (!nameFound) {
        cout << "No sets found matching that search term." << endl;
    }
    else {
        int sizeResult = result.size();
        for (int i = 0; i < sizeResult; i += 2) {
        cout << data.at(result.at(i)).at(result.at(i + 1)).numberID;
        cout << " " << data.at(result.at(i)).at(result.at(i + 1)).name;
        cout << " $" << data.at(result.at(i)).at(result.at(i + 1)).price << endl;
        }
    }
}

void ThemeSearch(vector<vector <LegoProduct> >& data) {
    int numOfCollections = data.size();
    bool nameFound = false;
    int numOfSets = 0;
    vector<int> result;

    string searchTerm;
    cin >> searchTerm;
    cin.get();
    for (int collection = 0; collection < numOfCollections; collection++) {
        numOfSets = data.at(collection).size();
        cout << "Num of Sets " << numOfSets << endl;
        for (int set = 0; set < numOfSets; set++) {
            if (data.at(collection).at(set).theme.find(searchTerm) != string::npos) {
                nameFound = true;
                result.push_back(collection);
                result.push_back(set);
            } 
        }
    }
    if (!nameFound) {
        cout << "No sets found matching that search term." << endl;
    }
    else {
        int sizeResult = result.size();
        for (int i = 0; i < sizeResult; i += 2) {
        cout << data.at(result.at(i)).at(result.at(i + 1)).numberID;
        cout << " " << data.at(result.at(i)).at(result.at(i + 1)).name;
        cout << " $" << data.at(result.at(i)).at(result.at(i + 1)).price << endl;
        }
    }
}

void AvgNumOfPartsInSets(vector <vector <LegoProduct> >& data) {
	int numOfCollections = data.size();
	int numOfSets = 0;
	unsigned int totalNumOfParts = 0;
	unsigned int totalNumOfSets = 0;
    for (int collection = 0; collection < numOfCollections; collection++) {
        numOfSets = data.at(collection).size();
		totalNumOfSets += numOfSets;
        for (int set = 0; set < numOfSets; set++) {
			totalNumOfParts += data.at(collection).at(set).numOfPieces;
        }
    }
	cout << "Average part count for " << totalNumOfSets << " sets: ";
	cout << (totalNumOfParts / totalNumOfSets) << endl;
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
	vector<vector <LegoProduct> > legoProductVect;
	vector<LegoProduct> legoProductVectorTest;
    vector<LegoProduct> lego1;
    vector<LegoProduct> lego2;
	vector<LegoProduct> lego3;

	switch (option)
	{
		case 1:
            legoDatatInput.open("test.csv");
			legoProductVect.push_back(lego1);
            ReadLegoData(legoDatatInput, legoProductVect.at(0));
            legoDatatInput.close();
			break;
		case 2:
            legoDatatInput.open("lego2.csv");
			legoProductVect.push_back(lego2);
            ReadLegoData(legoDatatInput, legoProductVect.at(1)); // THIS WON"T WORK
            legoDatatInput.close();
			break;
		case 3:
            legoDatatInput.open("lego3.csv");
			legoProductVect.push_back(lego3);
            ReadLegoData(legoDatatInput, legoProductVect.at(2));
            legoDatatInput.close();
			break;
		case 4:
            legoDatatInput.open("lego1.csv");
			legoProductVect.push_back(lego1);
            ReadLegoData(legoDatatInput, legoProductVect.at(0));
            legoDatatInput.close();
            legoDatatInput.open("lego2.csv");
			legoProductVect.push_back(lego2);
            ReadLegoData(legoDatatInput, legoProductVect.at(1));
            legoDatatInput.close();
            legoDatatInput.open("lego3.csv");
			legoProductVect.push_back(lego3);
            ReadLegoData(legoDatatInput, legoProductVect.at(2));
            legoDatatInput.close();
            legoDatatInput.open("test.csv");
			legoProductVect.push_back(legoProductVectorTest);
            ReadLegoData(legoDatatInput, legoProductVect.at(3));
            legoDatatInput.close();
			break;
		case 5: 
			legoDatatInput.open("test.csv");
			ReadLegoData(legoDatatInput, legoProductVectorTest);
			legoProductVect.push_back(lego1);
            ReadLegoData(legoDatatInput, legoProductVect.at(0));
			break;
		default:
			break;
	}

    PrintNumOfDataRecorded(legoProductVect);
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
    int sizeTest; // TODO delete
	cin >> choice;
   cin.get();  // Clear newline character for any later input
   
   /*======= Print out how many sets were loaded =======*/
   /*======= Based on the choice, execute the appropriate task and show the results =======*/
	switch (choice)
	{
		case 1:
            MostExpensiveProdcut(legoProductVect);
			break;
		case 2:
            LargestPieceCount(legoProductVect);
			break;
		case 3:
            NameSearch(legoProductVect);
			break;
		case 4:
            ThemeSearch(legoProductVect);
			break;
		case 5: 
			AvgNumOfPartsInSets(legoProductVect);
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
				cout << legoProductVectorTest.at(i).numberID;
				cout << ", "; 
				cout << legoProductVectorTest.at(i).theme;
				cout << ", "; 
				cout << legoProductVectorTest.at(i).name;
				cout << ", "; 
				cout << legoProductVectorTest.at(i).numOfMinifigs;
				cout << ", "; 
				cout << legoProductVectorTest.at(i).numOfPieces;
				cout << ", "; 
				cout << legoProductVectorTest.at(i).price;
				cout << endl;
			}
			break;
		case 10:
            sizeTest = legoProductVect.at(0).size();
			for (int i = 0; i < sizeTest; i++) {
				cout << legoProductVect.at(0).at(i).numberID;
				cout << ", "; 
				cout << legoProductVect.at(0).at(i).theme;
				cout << ", "; 
				cout << legoProductVect.at(0).at(i).name;
				cout << ", "; 
				cout << legoProductVect.at(0).at(i).numOfMinifigs;
				cout << ", "; 
				cout << legoProductVect.at(0).at(i).numOfPieces;
				cout << ", "; 
				cout << legoProductVect.at(0).at(i).price;
				cout << endl;
			}
			break;
		default:
			break;
	}
   
	return 0;
}


