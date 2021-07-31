#include "Color.h"

Color::Color(const char* _name, int _color) {
    SetName(_name);
    SetValue(_color);
    hexFromInt();
}

void Color::SetValue(int value) {
    colorValue = value;
}

void Color::SetName(const char* name) {
    for(int i = 0; name[i] != '\0'; i++) {
        nameOfColor.push_back(name[i]);
    }
}

// Accessors
int Color::GetInt() const {
    return colorValue;
}

unsigned char Color::GetR() const {
    unsigned char fullByte = 255;
    return ((colorValue >> 16) & fullByte);
}

unsigned char Color::GetG() const {
    unsigned char fullByte = 255;
    return ((colorValue >> 8) & fullByte);
}

unsigned char Color::GetB() const {
    unsigned char fullByte = 255;
    return (colorValue & fullByte);
}

std::string Color::GetHexValue() const {
    return hexValue;
}

void Color::hexFromInt() {
    std::string result = "0x";
    unsigned char temp = GetR();
    result.push_back(numToHex((int)temp / 16));
    result.push_back(numToHex((int)temp % 16));
    temp = GetG();
    result.push_back(numToHex((int)temp / 16));
    result.push_back(numToHex((int)temp % 16));
    temp = GetB();
    result.push_back(numToHex((int)temp / 16));
    result.push_back(numToHex((int)temp % 16));

    hexValue = result;
}

std::string Color::GetName() const {
    return nameOfColor;
}

unsigned char Color::numToHex(int in) const{
    switch (in) {
    case 0:
        return '0';
        break;
    case 1:
        return '1';
        break;
    case 2:
        return '2';
        break;
    case 3:
        return '3';
        break;
    case 4:
        return '4';
        break;
    case 5:
        return '5';
        break;
    case 6:
        return '6';
        break;
    case 7:
        return '7';
        break;
    case 8:
        return '8';
        break;
    case 9:
        return '9';
        break;
    case 10:
        return 'A';
        break;
    case 11:
        return 'B';
        break;
    case 12:
        return 'C';
        break;
    case 13:
        return 'D';
        break;
    case 14:
        return 'E';
        break;
    case 15:
        return 'F';
        break;
    default:
        return 'Z';
        break;
    }
}
