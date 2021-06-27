
#include "extrafile.h"

/********************************************************************************
 * **** Constructor/Copy Assignment operator/ Copy Constructor/Destructor/etc ***
 * ******************************************************************************/

LegoProductCatalog::LegoProductCatalog() {}

LegoProductCatalog::LegoProductCatalog(ifstream& dataFile) {
    ReadLegoData(dataFile);
}

LegoProductCatalog::LegoProductCatalog(LegoProductCatalog& rhs) {
    int sizeCollection = rhs.LegoProductVect.size();
    int sizeSets = 0;
    for (int i = 0; i < sizeCollection; i++) {
        sizeSets = rhs.LegoProductVect.at(i).size();
        vector <LegoProduct> LegoProductCollection;
        this->LegoProductVect.push_back(LegoProductCollection);
        for (int j = 0; j < sizeSets; j++) {
			LegoProduct* temp = new LegoProduct;
            temp->numberID = rhs.LegoProductVect.at(i).at(j).numberID;
            temp->name = rhs.LegoProductVect.at(i).at(j).name;
            temp->theme = rhs.LegoProductVect.at(i).at(j).theme;
            temp->numOfMinifigs = rhs.LegoProductVect.at(i).at(j).numOfMinifigs;
            temp->numOfPieces = rhs.LegoProductVect.at(i).at(j).numOfPieces;
            temp->price = rhs.LegoProductVect.at(i).at(j).price;
            this->LegoProductVect.at(i).push_back(*temp);
        }
    }
}

LegoProductCatalog& LegoProductCatalog::operator=(LegoProductCatalog& rhs) {
    int sizeCollection = rhs.LegoProductVect.size();
    int sizeSets = 0;
    for (int i = 0; i < sizeCollection; i++) {
        sizeSets = rhs.LegoProductVect.at(i).size();
        vector <LegoProduct> LegoProductCollection;
        this->LegoProductVect.push_back(LegoProductCollection);
        for (int j = 0; j < sizeSets; j++) {
			LegoProduct* temp = new LegoProduct;
            temp->numberID = rhs.LegoProductVect.at(i).at(j).numberID;
            temp->name = rhs.LegoProductVect.at(i).at(j).name;
            temp->theme = rhs.LegoProductVect.at(i).at(j).theme;
            temp->numOfMinifigs = rhs.LegoProductVect.at(i).at(j).numOfMinifigs;
            temp->numOfPieces = rhs.LegoProductVect.at(i).at(j).numOfPieces;
            temp->price = rhs.LegoProductVect.at(i).at(j).price;
            this->LegoProductVect.at(i).push_back(*temp);
        }
    }
    return *this; 
}

LegoProductCatalog::~LegoProductCatalog() {
}

/********************************************************************************
 * ********************** Read in Data Behavior *********************************
 * ******************************************************************************/

void LegoProductCatalog::ReadLegoData(ifstream& dataFile) {
    vector <LegoProduct> LegoProductCollection;
    //this->LegoProductVect.push_back(LegoProductCollection);

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
		while (getline(dataFile, buffer, ',')){
			LegoProduct* temp = new LegoProduct;
			//cout << "buffer is " << buffer << endl; //TODO remove
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

			LegoProductCollection.push_back(*temp);
		}
	}
    this->LegoProductVect.push_back(LegoProductCollection);
}

/********************************************************************
 ********* Display Behaviour ****************************************
 *******************************************************************/

void LegoProductCatalog::PrintAmountOfDataLoaded() {
    unsigned int numOfDataLoaded = 0;
    int size = LegoProductVect.size();
    for (int i = 0; i < size; i++) {
        numOfDataLoaded += LegoProductVect.at(i).size();
    }
    cout << "Total number of sets: " << numOfDataLoaded << endl;
}
 
void LegoProductCatalog::DisplayFullSetInfo(LegoProduct& catalog) {
    cout << "Name: " << catalog.name << endl;
    cout << "Number: " << catalog.numberID << endl;
    cout << "Theme: " << catalog.theme << endl;
    cout << "Price: $" << catalog.price << endl;
    cout << "Minifigures: " << catalog.numOfMinifigs<< endl;
    cout << "Piece count: " << catalog.numOfPieces << endl;
}

// This is used for t/s and debugging, displays data in same format as file on 1 line
void LegoProductCatalog::DisplayFullSetInfoOneLine() {
    int size = LegoProductVect.at(0).size();
    cout << "size: " << size << endl;
    for (int i = 0; i < size; i++) {
        cout << LegoProductVect.at(0).at(i).numberID;
        cout << ", " << LegoProductVect.at(0).at(i).theme;
        cout << ", " << LegoProductVect.at(0).at(i).name;
        cout << ", " << LegoProductVect.at(0).at(i).numOfMinifigs;
        cout << ", " << LegoProductVect.at(0).at(i).numOfPieces;
        cout << ", " << LegoProductVect.at(0).at(i).price << endl;
    }
}

void LegoProductCatalog::MostExpensiveProduct() {
    int mostExpenseiveSet = 0;
    int collectionWithMostExpensiveSet = 0;
    int numOfCollections = LegoProductVect.size();
    int numOfSets = 0;
    for (int collection = 0; collection < numOfCollections; collection++) {
        numOfSets = LegoProductVect.at(collection).size();
        for (int set = 0; set < numOfSets; set++) {
            if (LegoProductVect.at(collection).at(set).price > LegoProductVect.at(collectionWithMostExpensiveSet).at(mostExpenseiveSet).price) {
                mostExpenseiveSet = set;
                collectionWithMostExpensiveSet = collection;
            } 
        }
    }
    cout << "The most expensive set is: " << endl;
    DisplayFullSetInfo(LegoProductVect.at(collectionWithMostExpensiveSet).at(mostExpenseiveSet));
}

void LegoProductCatalog::LargestPieceCount() {
    int largestPieceCountSet = 0;
    int collectionWithSetWithLargePieceCount = 0;
    int numOfCollections = LegoProductVect.size();
    int numOfSets = 0;
    for (int collection = 0; collection < numOfCollections; collection++) {
        numOfSets = LegoProductVect.at(collection).size();
        for (int set = 0; set < numOfSets; set++) {
            if (LegoProductVect.at(collection).at(set).numOfPieces > LegoProductVect.at(collectionWithSetWithLargePieceCount).at(largestPieceCountSet).numOfPieces) {
                largestPieceCountSet = set;
                collectionWithSetWithLargePieceCount = collection;
            } 
        }
    }
    cout << "The set with the highest parts count: " << endl;
    DisplayFullSetInfo(LegoProductVect.at(collectionWithSetWithLargePieceCount).at(largestPieceCountSet));
}

void LegoProductCatalog::NameSearch() {
    int numOfCollections = LegoProductVect.size();
    bool nameFound = false;
    int numOfSets = 0;
    // All sets that match, the search, their collectiona nd set number is stored in the 
    // resutls array.  element 0 is collection index element 1 is set index, this pattern continues.
    vector<int> result; 

    // Search term USER INPUT
    string searchTerm;
    getline(cin, searchTerm, '\n');

    // Search for all Names that contain the search term
    for (int collection = 0; collection < numOfCollections; collection++) {
        numOfSets = LegoProductVect.at(collection).size();
        for (int set = 0; set < numOfSets; set++) {
            if (LegoProductVect.at(collection).at(set).name.find(searchTerm) != string::npos) {
                nameFound = true;
                result.push_back(collection);
                result.push_back(set);
            } 
        }
    }

    // Display results
    if (!nameFound) {
        cout << "No sets found matching that search term" << endl;
    }
    else {
        cout << "Sets matching \"" << searchTerm << "\":" << endl;
        int sizeResult = result.size();
        for (int i = 0; i < sizeResult; i += 2) {
            cout << LegoProductVect.at(result.at(i)).at(result.at(i + 1)).numberID;
            cout << " " << LegoProductVect.at(result.at(i)).at(result.at(i + 1)).name;
            cout << " $" << LegoProductVect.at(result.at(i)).at(result.at(i + 1)).price << endl;
        }
    }
}

void LegoProductCatalog::ThemeSearch() {
    int numOfCollections = LegoProductVect.size();
    bool nameFound = false;
    int numOfSets = 0;
    vector<int> result;

    // Search term USER INPUT
    string searchTerm;
    getline(cin, searchTerm, '\n');

    // Search for all themes that contain the search term
    for (int collection = 0; collection < numOfCollections; collection++) {
        numOfSets = LegoProductVect.at(collection).size();
        for (int set = 0; set < numOfSets; set++) {
            if (LegoProductVect.at(collection).at(set).theme.find(searchTerm) != string::npos) {
                nameFound = true;
                result.push_back(collection);
                result.push_back(set);
            } 
        }
    }

    // Display results
    if (!nameFound) {
        cout << "No sets found matching that search term" << endl;
    }
    else {
        cout << "Sets matching \"" << searchTerm << "\":" << endl;
        int sizeResult = result.size();
        for (int i = 0; i < sizeResult; i += 2) {
            cout << LegoProductVect.at(result.at(i)).at(result.at(i + 1)).numberID;
            cout << " " << LegoProductVect.at(result.at(i)).at(result.at(i + 1)).name;
            cout << " $" << LegoProductVect.at(result.at(i)).at(result.at(i + 1)).price << endl;
        }
    }
}

void LegoProductCatalog::AvgNumOfPartsInSets() {
	int numOfCollections = LegoProductVect.size();
	int numOfSets = 0;
	unsigned int totalNumOfParts = 0;
	unsigned int totalNumOfSets = 0;
    for (int collection = 0; collection < numOfCollections; collection++) {
        numOfSets = LegoProductVect.at(collection).size();
		totalNumOfSets += numOfSets;
        for (int set = 0; set < numOfSets; set++) {
			totalNumOfParts += LegoProductVect.at(collection).at(set).numOfPieces;
        }
    }
    // The following make 1 line of outpoint
	cout << "Average part count for " << totalNumOfSets << " sets: ";
	cout << (totalNumOfParts / totalNumOfSets) << endl;
}

void LegoProductCatalog::PriceInformation() {
    double totalCost = 0;
    double priceOfCheapestSet = LegoProductVect.at(0).at(0).price;
    double priceOfMostExpensiveSet = 0;
    int cheapestSet = 0;
    int collectionWithCheapestSet = 0;
    int mostExpensiveSet = 0;
    int collectionWithMostExpensiveSet = 0;
	int numOfCollections = LegoProductVect.size();
	int numOfSets = 0;
	unsigned int totalNumOfSets = 0;

    // Linear search
    for (int collection = 0; collection < numOfCollections; collection++) {
        numOfSets = LegoProductVect.at(collection).size();
		totalNumOfSets += numOfSets;
        for (int set = 0; set < numOfSets; set++) {
            totalCost += LegoProductVect.at(collection).at(set).price;
            // Find most expensive
            if (LegoProductVect.at(collection).at(set).price > priceOfMostExpensiveSet) {
                mostExpensiveSet = set;
                collectionWithMostExpensiveSet = collection;
                priceOfMostExpensiveSet = LegoProductVect.at(collection).at(set).price;
            }
            // Find cheapst
            if (LegoProductVect.at(collection).at(set).price < priceOfCheapestSet) {
                cheapestSet = set;
                collectionWithCheapestSet = collection;
                priceOfCheapestSet = LegoProductVect.at(collection).at(set).price;
            }
        }
    }
    // The following make 1 line of outpoint
    cout << "Average price for " << totalNumOfSets << " sets: $" << (totalCost / (double)totalNumOfSets) << endl;
    cout << endl;
    cout << "Least expensive set: " << endl;
    DisplayFullSetInfo(LegoProductVect.at(collectionWithCheapestSet).at(cheapestSet));
    cout << endl;
    cout << "Most expensive set: " << endl;
    DisplayFullSetInfo(LegoProductVect.at(collectionWithMostExpensiveSet).at(mostExpensiveSet));
}

void LegoProductCatalog::MinifigureInfo() {
	int numOfCollections = LegoProductVect.size();
	int numOfSets = 0;
	unsigned int totalNumOfMinifigures = 0;
	unsigned int totalNumOfSets = 0;
    int collectionWithMostMinifigures = 0;
    int setWithMostMinifigures = 0;
    unsigned int mostMinifigures = 0;

    for (int collection = 0; collection < numOfCollections; collection++) {
        numOfSets = LegoProductVect.at(collection).size();
		totalNumOfSets += numOfSets;
        for (int set = 0; set < numOfSets; set++) {
			totalNumOfMinifigures += LegoProductVect.at(collection).at(set).numOfMinifigs;
            if (LegoProductVect.at(collection).at(set).numOfMinifigs > mostMinifigures) {
                collectionWithMostMinifigures = collection;
                setWithMostMinifigures = set;
                mostMinifigures = LegoProductVect.at(collection).at(set).numOfMinifigs;
            }
        }
    }
    // The following make 1 line of outpoint
	cout << "Average number of minifigures: " << (totalNumOfMinifigures / totalNumOfSets) << endl;
    cout << endl;
    cout << "Set with the most minifigures: " << endl;
    DisplayFullSetInfo(LegoProductVect.at(collectionWithMostMinifigures).at(setWithMostMinifigures));
}

void LegoProductCatalog::BuyOneOfEverything() {
	int numOfCollections = LegoProductVect.size();
	int numOfSets = 0;
	unsigned int totalNumOfMinifigures = 0;
	double totalCost = 0.0f;
	unsigned int totalNumOfPieces = 0;

    // Linearly add up all values
    for (int collection = 0; collection < numOfCollections; collection++) {
        numOfSets = LegoProductVect.at(collection).size();
        for (int set = 0; set < numOfSets; set++) {
			totalCost += LegoProductVect.at(collection).at(set).price;
			totalNumOfPieces += LegoProductVect.at(collection).at(set).numOfPieces;
			totalNumOfMinifigures += LegoProductVect.at(collection).at(set).numOfMinifigs;
        }
    }
    cout << "If you bought one of everything..." << endl;
    cout << "It would cost: $" << totalCost << endl;
    cout << "You would have " << totalNumOfPieces << " pieces in your collection" << endl;
    cout << "You would have an army of " << totalNumOfMinifigures << " minifigures!" << endl;
}