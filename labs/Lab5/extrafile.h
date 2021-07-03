#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using std::ifstream;
using std::vector;
using std::cout;
using std::endl;
#include "leaker.h"

class StarShipHangar {

    public: 

    struct Weapon {
        char* nameOfWeapon;
        int powerOfWeapon;
        float powerConsumptionOfWeapon;
    };

    struct StarShip {
        char* nameOfShip;
        char* classOfShip;
        short lengthOfShip;
        int shieldCapcityOfShip;
        float warpSpeedOfShip;
        int numOfWeaponsOnShip;
        vector<StarShipHangar::Weapon> weaponsOnShip;
    };

    vector<StarShip> starFleet;

    // Constructor, copy constructor, copy helper, and Destructor
    StarShipHangar();
    StarShipHangar(StarShipHangar& rhs);
    StarShipHangar& operator=(StarShipHangar& rhs); 
    StarShipHangar& CopyHelper(StarShipHangar& rhs);
    ~StarShipHangar();

    // Read in
    void readSpaceShipFileBinary(ifstream& data);

    // Print out Data
    void printStarShip(StarShip& starShip);
    void printAllStarShip();
    void printShipWithStrongestWeapon();
    void printStrongestShipWithWeapons();
    void printWeakestShipWithWeapons();
    void printUnarmedShips();
};