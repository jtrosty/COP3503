#pragma once
#include <vector>
#include "Vehicle.h"
using std::vector;

class Showroom {
    string _name;
    vector<Vehicle> _vehiclesInShowroom;
    int _capacity;

    public:
    // Default Constructor
    Showroom(string _name = "Unnamed", unsigned int _capacity = 0);

    // Accessor/Gettor
    vector<Vehicle> GetVehicleList();
    
    void AddVehicle(Vehicle v);
    void ShowInventory();
    float GetInventoryValue();
};
