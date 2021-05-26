#pragma once
#include <vector>
#include "Vehicle.h"
using std::vector;

class Showroom {
    string name;
    vector<Vehicle> vehiclesInShowroom();
    int capacity;

    public:
    // Default Constructor
    Showroom(string _name = "Generic Dealerhsip", unsigned int _capacity = 0);

    // Accessor/Gettor
    vector<Vehicle> GetVehicleList();
    
    void AddVehicle(Vehicle v);
    void ShowInventory();
    float GetInventoryValue();
};
