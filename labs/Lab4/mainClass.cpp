#include <iomanip>
#include <iostream>
#include "extrafile.h"
using namespace std;

/**************************************************************
 * ******** lAB 4 with Object and comments *******************
 * ***********************************************************/

int main()
{
	ifstream legoDataInput;
	cout << std::fixed << setprecision(2);
	cout << "Which file(s) to open?\n";
	cout << "1. lego1.csv" << endl;
	cout << "2. lego2.csv" << endl;
	cout << "3. lego3.csv" << endl;
	cout << "4. All 3 files" << endl;
	int option;
	cin >> option;

	LegoProductCatalog LegoCatalog; 
   /*======= Load data from file(s) =======*/

	switch (option)
	{
		case 1:
			legoDataInput.open("lego1.csv");
			LegoCatalog.ReadLegoData(legoDataInput);
			legoDataInput.close();
			break;
		case 2:
			legoDataInput.open("lego2.csv");
			LegoCatalog.ReadLegoData(legoDataInput);
			legoDataInput.close();
			break;
		case 3:
			legoDataInput.open("lego3.csv");
			LegoCatalog.ReadLegoData(legoDataInput);
			legoDataInput.close();
			break;
		case 4:
			legoDataInput.open("lego1.csv");
			LegoCatalog.ReadLegoData(legoDataInput);
			legoDataInput.close();
			legoDataInput.open("lego2.csv");
			LegoCatalog.ReadLegoData(legoDataInput);
			legoDataInput.close();
			legoDataInput.open("lego3.csv");
			LegoCatalog.ReadLegoData(legoDataInput);
			legoDataInput.close();
			/*
			legoDataInput.open("test.csv");
			LegoCatalog.ReadLegoData(legoDataInput);
			legoDataInput.close();
			*/
			break;
		default:
			break;
	}
   
   cout << "1. Most Expensive set" << endl;
	cout << "2. Largest piece count" << endl;
	cout << "3. Search for set name containing..." << endl;
	cout << "4. Search themes..." << endl;
	cout << "5. Part count information" << endl;
	cout << "6. Price information" << endl;
	cout << "7. Minifigure information" << endl;
	cout << "8. If you bought one of everything..." << endl;
	cout << "0. Exit" << endl;

	LegoCatalog.PrintAmountOfDataLoaded();
   
	int choice;
	cin >> choice;
   cin.get();  // Clear newline character for any later input
   
   /*======= Print out how many sets were loaded =======*/
   /*======= Based on the choice, execute the appropriate task and show the results =======*/
   
	switch (choice)
	{
		case 1:
			LegoCatalog.MostExpensiveProduct();
			break;
		case 2:
			LegoCatalog.LargestPieceCount();
			break;
		case 3:
			LegoCatalog.NameSearch();
			break;
		case 4:
			LegoCatalog.ThemeSearch();
			break;
		case 5: 
			LegoCatalog.AvgNumOfPartsInSets();
			break;
		case 6:
			LegoCatalog.PriceInformation();
			break;
		case 7:
			LegoCatalog.MinifigureInfo();
			break;
		case 8:
			LegoCatalog.BuyOneOfEverything();
			break;
		case 0:
			break;
		case 10:
			LegoCatalog.DisplayFullSetInfoOneLine();
			break;
		default:
			break;
	}
   
	return 0;
}


