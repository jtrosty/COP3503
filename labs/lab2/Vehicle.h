#include <string>
using std::string;

class Vehicle {
    string _make;
    string _model;
    int _year;
    float _price;
    unsigned int _mileage;
    
public:
    // Default constructor, initializes variable sto default values
    Vehicle();
    Vehicle(string make, string model, int year, float price, int mileage);

    // Print out the vehciale's details in a single line:
    // 1973 Ford Mustang $9500 113000
    void Display();

    // Create and return a single string in form of "YEAR MAKE MODEL"
    // EX: "1970 Ford Mustang"
    string GetYearMakeModel();

    // Return the price
    float GetPrice();

};
