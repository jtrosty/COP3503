#include <vector>
#include "Vehicle.h"
using std::vector;

class Showroom {
    string _name;
    vector<Vehicle> _showroom();

    public:
    // Default Constructor
    Showroom(string name, int capacity);

    // Accessor/Gettor
    vector<Vehicle> GetVehicleList();
    
    void AddVehicle(Vehicle v);
    void ShowInventory();
    float GetInventoryValue();

};
