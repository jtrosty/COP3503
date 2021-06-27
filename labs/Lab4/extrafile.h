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

class LegoProductCatalog {

    struct LegoProduct {
        unsigned int numberID;
        string theme;
        string name;
        unsigned int numOfMinifigs;
        unsigned int numOfPieces;
        double price;
    };

    vector<vector <LegoProduct> > LegoProductVect; 

    public:

    // Constructor
    LegoProductCatalog();
    LegoProductCatalog(ifstream& dataFile);

    // Copy Constructor

    // Destructor 
    ~LegoProductCatalog();


    // Read in Data Behavior
    void ReadLegoData(ifstream& dataFile);

    // Display Behavior
    void PrintAmountOfDataLoaded();
    void DisplayFullSetInfo(LegoProduct& catalog);
    void DisplayFullSetInfoOneLine();
    void MostExpensiveProduct();
    void LargestPieceCount();
    void NameSearch();
    void ThemeSearch();
    void AvgNumOfPartsInSets();
    void PriceInformation();
    void MinifigureInfo();
    void BuyOneOfEverything();
};
