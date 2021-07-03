#include "extrafile.h"
#include "leaker.h"

//******************************************************************
// Constructor, copy constructor, copy helper, and Destructor
//******************************************************************
StarShipHangar::StarShipHangar() {

}

StarShipHangar::StarShipHangar(StarShipHangar& rhs) {
    int size = rhs.starFleet.size();
    for (int i = 0; i < size; i++) {
        this->starFleet.push_back(rhs.starFleet.at(i));
    }
}

StarShipHangar& StarShipHangar::operator=(StarShipHangar& rhs) {
    int size = rhs.starFleet.size();
    for (int i = 0; i < size; i++) {
        this->starFleet.push_back(rhs.starFleet.at(i));
    }
    return *this;
}

StarShipHangar& StarShipHangar::CopyHelper(StarShipHangar& rhs) {
    int size = rhs.starFleet.size();
    for (int i = 0; i < size; i++) {
        this->starFleet.push_back(rhs.starFleet.at(i));
    }
    return *this;
}

StarShipHangar::~StarShipHangar() {
    int size = this->starFleet.size();
    for (int i = 0; i < size; i++) {
        delete this->starFleet.at(i).nameOfShip;
        delete this->starFleet.at(i).classOfShip;

        int numOfWeapons = this->starFleet.at(i).numOfWeaponsOnShip;
        for (int j = 0; j < numOfWeapons; j++) {
            delete this->starFleet.at(i).weaponsOnShip.at(j).nameOfWeapon;
        }
        this->starFleet.at(i).weaponsOnShip.clear();
        delete &starFleet.at(i);
    }
    //this->starFleet.clear();
}

/**************************************************************************************
 * *********************** READ IN DATA BEHAVIOR **************************************
 * ************************************************************************************/

void StarShipHangar::readSpaceShipFileBinary(ifstream& data) {
    int numOfSpaceships;
    data.read((char*)&numOfSpaceships, sizeof(int));
    StarShip* starShip = new StarShip;

    for (int i = 0; i < numOfSpaceships; i++) {
        int lengthOfString;
        data.read((char*)&lengthOfString, sizeof(int));
        starShip->nameOfShip = new char[lengthOfString];
        data.read(starShip->nameOfShip, lengthOfString);

        data.read((char*)&lengthOfString, sizeof(int));
        starShip->classOfShip = new char[lengthOfString];
        data.read(starShip->classOfShip, lengthOfString);

        data.read((char*)&starShip->lengthOfShip, sizeof(short));
        data.read((char*)&starShip->shieldCapcityOfShip, sizeof(int));
        data.read((char*)&starShip->warpSpeedOfShip, sizeof(float));
        data.read((char*)&starShip->numOfWeaponsOnShip, sizeof(int));

        if (starShip->numOfWeaponsOnShip == 0) {
        }
        else {
            vector<StarShipHangar::Weapon> tempWeaponsOnShip;
            Weapon* tempWeapon = new Weapon;
            for (int i = 0; i < starShip->numOfWeaponsOnShip; i++) {

                data.read((char*)&lengthOfString, sizeof(int)); 
                tempWeapon->nameOfWeapon = new char[lengthOfString];

                data.read(tempWeapon->nameOfWeapon, lengthOfString);
                data.read((char*)&tempWeapon->powerOfWeapon, sizeof(int));
                data.read((char*)&tempWeapon->powerConsumptionOfWeapon, sizeof(float));

                tempWeaponsOnShip.push_back(*tempWeapon);
            }
            starShip->weaponsOnShip = tempWeaponsOnShip;
        }
        starFleet.push_back(*starShip);
    }
    delete starShip;
}

/**************************************************************************************
 * *********************** PRINT IN DATA BEHAVIOR **************************************
 * ************************************************************************************/

// All functions use this function to print the starship
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

// Contains the logic to find ship with strongest weapon
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

// Logic to find the strongest ship
void StarShipHangar::printStrongestShipWithWeapons() {
    int size = starFleet.size();
    int result = 0;
    int strongestTotalPower = 0;

    for (int i = 0; i < size; i++) {
        int powerOfShip = 0;

        if (this->starFleet.at(i).numOfWeaponsOnShip == 0 ) {
            continue;
        }
        else {
            for (int j = 0; j < starFleet.at(i).numOfWeaponsOnShip; j++) {                
                powerOfShip += starFleet.at(i).weaponsOnShip.at(j).powerOfWeapon;
            }
        }
        if (powerOfShip > strongestTotalPower) {
            result = i;
            strongestTotalPower = powerOfShip;
        }
    }
    printStarShip(starFleet.at(result));
}

// Prints the weakest whip with weapons
void StarShipHangar::printWeakestShipWithWeapons() {
    int size = starFleet.size();
    int result = 0;
    int weakestTotalPower = 0;

    for (int i = 0; i < size; i++) {
        int powerOfShip = 0;

        if (this->starFleet.at(i).numOfWeaponsOnShip == 0 ) {
            continue;
        }
        else {
            for (int j = 0; j < starFleet.at(i).numOfWeaponsOnShip; j++) {                
                powerOfShip += starFleet.at(i).weaponsOnShip.at(j).powerOfWeapon;
            }
        }
        if (i == 0) weakestTotalPower = powerOfShip;
        if (powerOfShip < weakestTotalPower) {
            result = i;
        }
    }
    printStarShip(starFleet.at(result));
}

// Cycles through unarmed ships and prints them
void StarShipHangar::printUnarmedShips() {
    int size = starFleet.size();
    for (int i = 0; i < size; i++) {
        if (starFleet.at(i).numOfWeaponsOnShip == 0) {
            printStarShip(starFleet.at(i));
        }
    }
}