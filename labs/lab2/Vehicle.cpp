#pragma once
#include "Vehicle.h"
#include <iostream>
using std::cout;
using std::endl;

// Default constructor, initializes variables to default values
Vehicle::Vehicle() {
    _make = "COP3503";
    _model = "Rust Bucket";
    _year = 1900;
    _price = 0;
    _mileage = 0;
}

Vehicle::Vehicle(string make, string model, int year, float price, int mileage) {
    _make = make;
    _model = model;
    _year = year;
    _price = price;
    _mileage = mileage;
}

// Print out the vehciale's details in a single line:
// 1973 Ford Mustang $9500 113000
void Vehicle::Display() {
    cout << _year << " " << _make << " " << _model << " $"
         << _price << " " << _mileage << endl;
    
}

// Create and return a single string in form of "YEAR MAKE MODEL"
// EX: "1970 Ford Mustang"
string Vehicle::GetYearMakeModel(){
    return std::to_string(_year) + " " + _make + " " + _model;

}

// Return the price
float Vehicle::GetPrice() {
    return _price;
}


