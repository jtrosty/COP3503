#include <string>
#include <map>
#include <iostream>
using std::cout;
using std::endl;

class Color {
    std::string nameOfColor;
    int colorValue;
    std::string hexValue;

    void hexFromInt();
    unsigned char numToHex(int in) const;


    public:
    // Contructor
    Color(const char* _name, int _color);

    // Given an integer value, convert it to RGB and Hex values
    void SetValue(int value);
    void SetName(const char *name);

    // Accessors
    int GetInt() const;
    unsigned char GetR() const;
    unsigned char GetG() const;
    unsigned char GetB() const;
    std::string GetHexValue() const;
    std::string GetName() const;
};