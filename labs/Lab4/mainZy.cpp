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

void DisplayFullSetInfo(LegoProduct& rha) {
    cout << "Name: " << rha.name << endl;
    cout << "Number: " << rha.numberID << endl;
    cout << "Theme: " << rha.theme << endl;
    cout << "Price: $" << rha.price << endl;
    cout << "Minifigures: " << rha.numOfMinifigs<< endl;
    cout << "Piece count: " << rha.numOfPieces << endl;
}

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
    for (unsigned int i = 0; i < data.size(); i++) {
        sumOfDataRecorded += data.at(i).size(); 
    }
    cout << "Total number of sets: " << sumOfDataRecorded << endl;
}

void MostExpensiveProdcut(vector<vector <LegoProduct> >& data) {
    int mostExpenseiveSet = 0;
    int collectionWithMostExpensiveSet = 0;
    int numOfCollections = data.size();
    int numOfSets = 0;
    for (int collection = 0; collection < numOfCollections; collection++) {
        numOfSets = data.at(collection).size();
        for (int set = 0; set < numOfSets; set++) {
            if (data.at(collection).at(set).price > data.at(collectionWithMostExpensiveSet).at(mostExpenseiveSet).price) {
                mostExpenseiveSet = set;
                collectionWithMostExpensiveSet = collection;
            } 
        }
    }
    cout << "The most expensive set is: " << endl;
    DisplayFullSetInfo(data.at(collectionWithMostExpensiveSet).at(mostExpenseiveSet));
    /*
    cout << "Name: " << data.at(collectionWithMostExpensiveSet).at(mostExpenseiveSet).name << endl;
    cout << "Number: " << data.at(collectionWithMostExpensiveSet).at(mostExpenseiveSet).numberID << endl;
    cout << "Theme: " << data.at(collectionWithMostExpensiveSet).at(mostExpenseiveSet).theme << endl;
    */ //TODO DELETE
}

void LargestPieceCount(vector<vector <LegoProduct> >& data) {
    int largestPieceCountSet = 0;
    int collectionWithSetWithLargePieceCount = 0;
    int numOfCollections = data.size();
    int numOfSets = 0;
    for (int collection = 0; collection < numOfCollections; collection++) {
        numOfSets = data.at(collection).size();
        for (int set = 0; set < numOfSets; set++) {
            if (data.at(collection).at(set).numOfPieces > data.at(collectionWithSetWithLargePieceCount).at(largestPieceCountSet).numOfPieces) {
                largestPieceCountSet = set;
                collectionWithSetWithLargePieceCount = collection;
            } 
        }
    }
    cout << "The set with the highest parts count: " << endl;
    DisplayFullSetInfo(data.at(collectionWithSetWithLargePieceCount).at(largestPieceCountSet));
}

void NameSearch(vector<vector <LegoProduct> >& data) {
    int numOfCollections = data.size();
    bool nameFound = false;
    int numOfSets = 0;
    vector<int> result;

    string searchTerm;
    getline(cin, searchTerm, '\n');

    for (int collection = 0; collection < numOfCollections; collection++) {
        numOfSets = data.at(collection).size();
        for (int set = 0; set < numOfSets; set++) {
            if (data.at(collection).at(set).name.find(searchTerm) != string::npos) {
                nameFound = true;
                result.push_back(collection);
                result.push_back(set);
            } 
        }
    }
    if (!nameFound) {
        cout << "No sets found matching that search term" << endl;
    }
    else {
        cout << "Sets matching \"" << searchTerm << "\":" << endl;
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
    getline(cin, searchTerm, '\n');
    for (int collection = 0; collection < numOfCollections; collection++) {
        numOfSets = data.at(collection).size();
        for (int set = 0; set < numOfSets; set++) {
            if (data.at(collection).at(set).theme.find(searchTerm) != string::npos) {
                nameFound = true;
                result.push_back(collection);
                result.push_back(set);
            } 
        }
    }
    if (!nameFound) {
        cout << "No sets found matching that search term" << endl;
    }
    else {
        cout << "Sets matching \"" << searchTerm << "\":" << endl;
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
    // The following make 1 line of outpoint
	cout << "Average part count for " << totalNumOfSets << " sets: ";
	cout << (totalNumOfParts / totalNumOfSets) << endl;
}

void PriceInformation(vector <vector <LegoProduct> >& data) {
    double totalCost = 0;
    double priceOfCheapestSet = data.at(0).at(0).price;
    double priceOfMostExpensiveSet = 0;
    int cheapestSet = 0;
    int collectionWithCheapestSet = 0;
    int mostExpensiveSet = 0;
    int collectionWithMostExpensiveSet = 0;
	int numOfCollections = data.size();
	int numOfSets = 0;
	unsigned int totalNumOfSets = 0;

    for (int collection = 0; collection < numOfCollections; collection++) {
        numOfSets = data.at(collection).size();
		totalNumOfSets += numOfSets;
        for (int set = 0; set < numOfSets; set++) {
            totalCost += data.at(collection).at(set).price;
            if (data.at(collection).at(set).price > priceOfMostExpensiveSet) {
                mostExpensiveSet = set;
                collectionWithMostExpensiveSet = collection;
                priceOfMostExpensiveSet = data.at(collection).at(set).price;
            }
            if (data.at(collection).at(set).price < priceOfCheapestSet) {
                cheapestSet = set;
                collectionWithCheapestSet = collection;
                priceOfCheapestSet = data.at(collection).at(set).price;
            }
        }
    }
    // The following make 1 line of outpoint
    cout << "Average price for " << totalNumOfSets << " sets: $" << (totalCost / (double)totalNumOfSets) << endl;
    cout << endl;
    cout << "Least expensive set: " << endl;
    DisplayFullSetInfo(data.at(collectionWithCheapestSet).at(cheapestSet));
    cout << endl;
    cout << "Most expensive set: " << endl;
    DisplayFullSetInfo(data.at(collectionWithMostExpensiveSet).at(mostExpensiveSet));
}

void MinifigureInfo(vector <vector <LegoProduct> >& data) {
	int numOfCollections = data.size();
	int numOfSets = 0;
	unsigned int totalNumOfMinifigures = 0;
	unsigned int totalNumOfSets = 0;
    int collectionWithMostMinifigures = 0;
    int setWithMostMinifigures = 0;
    unsigned int mostMinifigures = 0;

    for (int collection = 0; collection < numOfCollections; collection++) {
        numOfSets = data.at(collection).size();
		totalNumOfSets += numOfSets;
        for (int set = 0; set < numOfSets; set++) {
			totalNumOfMinifigures += data.at(collection).at(set).numOfMinifigs;
            if (data.at(collection).at(set).numOfMinifigs > mostMinifigures) {
                collectionWithMostMinifigures = collection;
                setWithMostMinifigures = set;
                mostMinifigures = data.at(collection).at(set).numOfMinifigs;
            }
        }
    }
    // The following make 1 line of outpoint
	cout << "Average number of minifigures: " << (totalNumOfMinifigures / totalNumOfSets) << endl;
    cout << endl;
    cout << "Set with the most minifigures: " << endl;
    DisplayFullSetInfo(data.at(collectionWithMostMinifigures).at(setWithMostMinifigures));
}

void BuyOneOfEverything(vector <vector <LegoProduct> >& data) {
	int numOfCollections = data.size();
	int numOfSets = 0;
	unsigned int totalNumOfMinifigures = 0;
	double totalCost = 0.0f;
	unsigned int totalNumOfPieces = 0;

    for (int collection = 0; collection < numOfCollections; collection++) {
        numOfSets = data.at(collection).size();
        for (int set = 0; set < numOfSets; set++) {
			totalCost += data.at(collection).at(set).price;
			totalNumOfPieces += data.at(collection).at(set).numOfPieces;
			totalNumOfMinifigures += data.at(collection).at(set).numOfMinifigs;
        }
    }
    cout << "If you bought one of everything..." << endl;
    cout << "It would cost: $" << totalCost << endl;
    cout << "You would have " << totalNumOfPieces << " pieces in your collection" << endl;
    cout << "You would have an army of " << totalNumOfMinifigures << " minifigures!" << endl;
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
            legoDatatInput.open("lego1.csv");
			legoProductVect.push_back(lego1);
            ReadLegoData(legoDatatInput, legoProductVect.at(0));
            legoDatatInput.close();
			break;
		case 2:
            legoDatatInput.open("lego2.csv");
			legoProductVect.push_back(lego2);
            ReadLegoData(legoDatatInput, legoProductVect.at(0)); // THIS WON"T WORK
            legoDatatInput.close();
			break;
		case 3:
            legoDatatInput.open("lego3.csv");
			legoProductVect.push_back(lego3);
            ReadLegoData(legoDatatInput, legoProductVect.at(0));
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
            /*
            legoDatatInput.open("test.csv");
			legoProductVect.push_back(legoProductVectorTest);
            ReadLegoData(legoDatatInput, legoProductVect.at(3));
            legoDatatInput.close();
            */
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

    cout << endl;
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

    PrintNumOfDataRecorded(legoProductVect);
    cout << endl;
   
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
            PriceInformation(legoProductVect);
			break;
		case 7:
            MinifigureInfo(legoProductVect);
			break;
		case 8:
            BuyOneOfEverything(legoProductVect);
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