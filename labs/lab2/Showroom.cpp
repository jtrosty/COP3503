#include "Showroom.h"
#include "Vehicle.h"
#include <iostream>
using std::cout;
using std::endl;

// Default Constructor
Showroom::Showroom(string _name, unsigned int _capacity) {
    name = _name;
    vehiclesInShowroom().resize(_capacity);
    capacity = _capacity;
}

// Accessor/Gettor
vector<Vehicle> Showroom::GetVehicleList() {
    return vehiclesInShowroom();
}

void Showroom::AddVehicle(Vehicle v) {
    if (vehiclesInShowroom().size() == vehiclesInShowroom().capacity()) {
        cout << "Showroom is full! Cannot add " << v.GetYearMakeModel() << endl;
    }
    else {
        vehiclesInShowroom().push_back(v);
    }
}

void Showroom::ShowInventory() {
    int size = vehiclesInShowroom().size();
    for(int i = 0; i < size; ++i) {
        vehiclesInShowroom().at(i).Display();
    }
}

float Showroom::GetInventoryValue() {
    float sumOfPrices = 0.0f;
    int size = vehiclesInShowroom().size();
    for (int i = 0; i < size; ++i) {
        sumOfPrices += vehiclesInShowroom().at(i).GetPrice();
    }
    return sumOfPrices;
}
