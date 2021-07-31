#include <string>
#include <map>
#include <iostream>
using std::cout;
using std::endl;

class Color {
    const char* nameOfColor;
    int colorValue;

    public:
    // Contructor
    Color();
    Color(const char* _name, int _color);

    // Given an integer value, convert it to RGB and Hex values
    void SetValue(int value);
    void SetName(const char *name);

    // Accessors
    const int GetInt() const;
    unsigned char GetR() const;
    unsigned char GetG() const;
    unsigned char GetB() const;
    std::string GetHexValue() const;
    std::string GetName() const;
};