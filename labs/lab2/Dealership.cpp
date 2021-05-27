#include "Dealership.h"
#include <iostream>
using std::cout;
using std::endl;

Dealership::Dealership(string name, unsigned int capacity) {
    _name = name;   
    _capacity = capacity;
}

void Dealership::AddShowroom(Showroom s) {
    if (_dealership.size() == _capacity)
        cout << "Dealership is full, can't add another showroom!" << endl;
    else {
        _dealership.push_back(s);
    }
}

float Dealership::GetAveragePrice() {
    float result = 0.0f;
    int numOfShowRooms = _dealership.size();
    for (int i = 0; i < numOfShowRooms; ++i) {
        result = _dealership.at(i).GetInventoryValue();
    }
}

// TODO fix the dealership show inventory
void Dealership::ShowInventory() {
    float average = 0.0f;
    int numOfShowRooms = _dealership.size();
    for (int i = 0; i < numOfShowRooms; ++i) {
        cout << "Vehicles in Room"
        _dealership.at(i).ShowInventory();
    }
    GetAveragePrice();
}