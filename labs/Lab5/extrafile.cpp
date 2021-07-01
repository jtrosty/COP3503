#include "extrafile.h"

//******************************************************************
// Constructor, copy constructor, copy helper, and Destructor
//******************************************************************
StarShipHangar::StarShipHangar() {

}

StarShipHangar& StarShipHangar::operator=(StarShipHangar& rhs) {

}

StarShipHangar& StarShipHangar::CopyHelper(StarShipHangar& rhs) {

}

StarShipHangar::~StarShipHangar() {

}

// Read in
void StarShipHangar::readSpaceShipFileBinary(ifstream& data) {
    int numOfSpaceships;
    data.read((char*)&numOfSpaceships, sizeof(int));
    cout << "# of spaceships: " << numOfSpaceships << endl;
    StarShip starShip;

    for (int i = 0; i < numOfSpaceships; i++) {
        int lengthOfString;
        data.read((char*)&lengthOfString, sizeof(int));
        starShip.nameOfShip = new char[lengthOfString];
        data.read(starShip.nameOfShip, lengthOfString);

        cout << "lenght of name: " << lengthOfString << endl;
        cout << "Name of 1st Ship: " << starShip.nameOfShip << endl;

        data.read((char*)&lengthOfString, sizeof(int));
        starShip.classOfShip = new char[lengthOfString];
        data.read(starShip.classOfShip, lengthOfString);

        cout << "lenght of class: " << lengthOfString << endl;
        cout << "Name of class: " << starShip.classOfShip << endl;
        data.read((char*)&starShip.lengthOfShip, sizeof(short));
        cout << "Length of Ship: " << starShip.lengthOfShip << endl;
        data.read((char*)&starShip.shieldCapcityOfShip, sizeof(int));
        cout << "Shield Capacity: " << starShip.shieldCapcityOfShip << endl;
        data.read((char*)&starShip.warpSpeedOfShip, sizeof(float));
        cout << "Warp speed: " << starShip.warpSpeedOfShip << endl;
        data.read((char*)&starShip.numOfWeaponsOnShip, sizeof(int));
        cout << "Num of Weapons: " << starShip.numOfWeaponsOnShip << endl;
        //weaponsOnShip.resize(numOfWeaponsOnShip);
        for (int i = 0; i < starShip.numOfWeaponsOnShip; i++) {
            Weapon temp;
            data.read((char*)&lengthOfString, sizeof(int)); 
            temp.nameOfWeapon = new char[lengthOfString];
            data.read(temp.nameOfWeapon, lengthOfString);
            data.read((char*)&temp.powerOfWeapon, sizeof(int));
            data.read((char*)&temp.powerConsumptionOfWeapon, sizeof(float));
            cout << "Name of Weapon: " << temp.nameOfWeapon << endl;
            cout << "Power of weapon: " << temp.powerOfWeapon << endl;
            cout << "Power consumption of weapon: " << temp.powerConsumptionOfWeapon << endl;
            starShip.weaponsOnShip.push_back(temp);
        }
        this->starFleet.push_back(starShip);
    }
}

void StarShipHangar::printStarShip(StarShip& ship) {
    cout << "Name: " << ship.nameOfShip << endl;
    cout << "Class: " << ship.classOfShip << endl;
    cout << "Length: " << ship.lengthOfShip << endl;
    cout << "Shield capacity: " << ship.shieldCapcityOfShip << endl;
    cout << "Maximum Warp: " << ship.warpSpeedOfShip << endl;
    cout << "Armaments: " << endl;
    if (ship.numOfWeaponsOnShip > 0) {
        int totalFirepower = 0;
        for (int i = 0; i < ship.numOfWeaponsOnShip; i++) {
            cout << ship.weaponsOnShip.at(i).nameOfWeapon << ", ";
            cout << ship.weaponsOnShip.at(i).powerOfWeapon << ", ";
            cout << ship.weaponsOnShip.at(i).powerConsumptionOfWeapon << endl;
            totalFirepower += ship.weaponsOnShip.at(i).powerOfWeapon;
        }
        cout << "Total firepower: " << totalFirepower << endl;
    }
    else {
        cout << "Unarmed" << endl;
    }
}

void StarShipHangar::printAllStarShip() {
    int size = starFleet.size();

    for (int i = 0; i < size; i++) {
        printStarShip(starFleet.at(i));
        cout << endl;
    }
}

void StarShipHangar::printShipWithStrongestWeapon() {
    int size = starFleet.size();
    int result = 0;
    int mostPowerfulWeapon = 0;

    for (int i = 0; i < size; i++) {
        if (this->starFleet.at(i).numOfWeaponsOnShip == 0 ) {
            continue;
        }
        else {
            for (int j = 0; j < starFleet.at(i).numOfWeaponsOnShip; j++) {
                if (starFleet.at(i).weaponsOnShip.at(j).powerOfWeapon >= mostPowerfulWeapon) {
                    result = i;
                    mostPowerfulWeapon = starFleet.at(i).weaponsOnShip.at(j).powerOfWeapon;
                }
            }
        }
    }
    printStarShip(starFleet.at(result));
}