#include <iostream>
#include <fstream>
#include <vector>
#include "extrafile.h"
using namespace std;
using std::cout;
using std::cin;
using std::endl;

void readSpaceShipFileBinary(ifstream& binaryData) {
    int numOfSpaceships;
    binaryData.read((char*)&numOfSpaceships, sizeof(int));
    cout << "# of spaceships: " << numOfSpaceships << endl;
    char* nameOfShip;
    char* classOfShip;
    short lengthOfShip;
    int shieldCapcityOfShip;
    float warSpeedOfShip;
    int numOfWeaponsOnShip;
    vector<char*> weaponsOnShip;
    char* weapon;
    int powerOfWeapon;
    float powerConsumptionOfWeapon;


    for (int i = 0; i < 1; i++) {
        int lengthOfName;

        binaryData.read((char*)&lengthOfName, sizeof(int));
        nameOfShip = new char[lengthOfName];
        binaryData.read(nameOfShip, lengthOfName);

        cout << "lenght of name: " << lengthOfName << endl;
        cout << "Name of 1st Ship: " << nameOfShip << endl;

        binaryData.read((char*)&lengthOfName, sizeof(int));
        classOfShip = new char[lengthOfName];
        binaryData.read(classOfShip, lengthOfName);

        cout << "lenght of class: " << lengthOfName << endl;
        cout << "Name of class: " << classOfShip << endl;
        binaryData.read((char*)&lengthOfShip, sizeof(short));
        cout << "Length of Ship: " << lengthOfShip << endl;
        binaryData.read((char*)&shieldCapcityOfShip, sizeof(int));
        cout << "Shield Capacity: " << shieldCapcityOfShip << endl;
        binaryData.read((char*)&warSpeedOfShip, sizeof(float));
        cout << "War speed: " << warSpeedOfShip << endl;
        binaryData.read((char*)&numOfWeaponsOnShip, sizeof(int));
        cout << "Num of Weapons: " << numOfWeaponsOnShip << endl;
        //weaponsOnShip.resize(numOfWeaponsOnShip);
        for (int i = 0; i < numOfWeaponsOnShip; i++) {
            binaryData.read((char*)&lengthOfName, sizeof(int)); 
            char* nameOfWeapon = new char[lengthOfName];
            binaryData.read(nameOfWeapon, lengthOfName);
            binaryData.read((char*)&powerOfWeapon, sizeof(int));
            binaryData.read((char*)&powerConsumptionOfWeapon, sizeof(float));
            cout << "Name of Weapon: " << nameOfWeapon << endl;
            cout << "Power of weapon: " << powerOfWeapon << endl;
            cout << "Power consumption of weapon: " << powerConsumptionOfWeapon << endl;
        }
        cout << "**************************" << endl;
    }
}

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
            readSpaceShipFileBinary(binaryInput);
            binaryInput.close();

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
            break;
        case 4:
            break;
        case 5:
            break;
    }

   /* Load files here */

	cout << "1. Print all ships" << endl;
	cout << "2. Starship with the strongest weapon" << endl;
	cout << "3. Strongest starship overall" << endl;
	cout << "4. Weakest ship (ignoring unarmed)" << endl;
	cout << "5. Unarmed ships" << endl;
	
	cin >> option;
	
	/* Work your magic here */
    switch (option) {
        case 1:
            fleet.printAllStarShip();
            break;
        case 2:
            fleet.printShipWithStrongestWeapon();
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
    }
	
   return 0;
}