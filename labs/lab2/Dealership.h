#pragma once
#include "Showroom.h"
#include <string>
#include <vector>
using std::vector;
using std::string;

class Dealership {
    string _name;
    int _capacity;
    vector<Showroom> _dealership;

    public:
    // Constructor
    Dealership(string name = "Generic Dealership", unsigned int capacity = 0);

    // Behaviors
    void AddShowroom(Showroom s);
    float GetAveragePrice();
    void ShowInventory();

};