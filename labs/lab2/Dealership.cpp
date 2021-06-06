#include "Dealership.h"
#include <iostream>
using std::cout;
using std::endl;

Dealership::Dealership(string name, unsigned int capacity) {
    _name = name;   
    _capacity = capacity;
}

// Add showroom if size < capcity
void Dealership::AddShowroom(Showroom s) {
    if (_dealership.size() == _capacity) // This com
        cout << "Dealership is full, can't add another showroom!" << endl;
    else {
        _dealership.push_back(s);
    }
}

// Get the average Price by collect total value of cars in dealership and 
// dividing by # of cars. 
float Dealership::GetAveragePrice() {
    float totalValue = 0.0f;
    int numOfCars = 0;
    int numOfShowRooms = _dealership.size();
    for (int i = 0; i < numOfShowRooms; ++i) {
        totalValue += _dealership.at(i).GetInventoryValue();
        numOfCars += _dealership.at(i).GetVehicleList().size();
    }
    if (numOfCars == 0) return 0.0f;
    else return (totalValue / numOfCars); 
}

/* Display Dealsher inventory in the following format
Dealership is full, can't add another showroom! 
Vehicles in Room One 
1998 Dodge Neon $500.00 932018

Vehicles in Room Two 
2001 Ford Escort $2000.00 125900 
2004 Ford F-150 $500.00 7392

Average car price: $1000.00
*/
void Dealership::ShowInventory() {
    int numOfShowRooms = _dealership.size();
    if (numOfShowRooms == 0) 
        cout << _name << " is empty!" << endl;
    else {
        for (int i = 0; i < numOfShowRooms; ++i) {
            _dealership.at(i).ShowInventory();
            cout << endl;
        }
    }
    cout << "Average car price: $" << GetAveragePrice();
}