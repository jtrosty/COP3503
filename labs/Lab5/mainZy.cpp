#include <iostream>
#include <fstream>
#include <vector>
#include "extrafile.h"
using namespace std;
using std::cout;
using std::cin;
using std::endl;
#include "leaker.h"

int main()
{
	cout << "Which file(s) to open?\n";
	cout << "1. friendlyships.shp" << endl;
	cout << "2. enemyships.shp" << endl;
	cout << "3. Both files" << endl;
	int option;
	cin >> option;
    ifstream binaryInput;
    StarShipHangar fleet; 

    switch (option) {
        case 1:
            binaryInput.open("friendlyships.shp", ios_base::in);
            fleet.readSpaceShipFileBinary(binaryInput);
            binaryInput.close();
            break;
        case 2:
            binaryInput.open("enemyships.shp", ios_base::in);
            fleet.readSpaceShipFileBinary(binaryInput);
            binaryInput.close();
            
            break;
        case 3:
            binaryInput.open("friendlyships.shp", ios_base::in);
            fleet.readSpaceShipFileBinary(binaryInput);
            binaryInput.close();

            binaryInput.open("enemyships.shp", ios_base::in);
            fleet.readSpaceShipFileBinary(binaryInput);
            binaryInput.close();
            break;
        case 4:
            break;
    }

   /* Load files here */

	cout << "1. Print all ships" << endl;
	cout << "2. Starship with the strongest weapon" << endl;
	cout << "3. Strongest starship overall" << endl;
	cout << "4. Weakest ship (ignoring unarmed)" << endl;
	cout << "5. Unarmed ships" << endl;
	
	cin >> option;
    cout << endl;
	
	/* Work your magic here */
    switch (option) {
        case 1:
            fleet.printAllStarShip();
            break;
        case 2:
            fleet.printShipWithStrongestWeapon();
            break;
        case 3:
            fleet.printStrongestShipWithWeapons();
            break;
        case 4:
            fleet.printWeakestShipWithWeapons();
            break;
        case 5:
            fleet.printUnarmedShips();
            break;
    }
	
   return 0;
}