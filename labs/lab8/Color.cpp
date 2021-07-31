#include "Color.h"

Color::Color() {
    cout << "made it" << endl;
}

Color::Color(const char* _name, int _color) {
    SetName(_name);
    SetValue(_color);
}

void Color::SetValue(int value) {
    colorValue = value;
}

void Color::SetName(const char* name) {
    nameOfColor = name;
}

// Accessors
const int Color::GetInt() const {
    return colorValue;
}

unsigned char Color::GetR() const {

}

unsigned char Color::GetG() const {

}

unsigned char Color::GetB() const {

}

std::string Color::GetHexValue() const {

}

std::string Color::GetName() const {

}