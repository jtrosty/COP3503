#include <string>

class Color {

    public:
    // Given an integer value, convert it to RGB and Hex values
    void SetValue(int value);
    void SetName(const char *name);

    // Accessors
    unsigned char GetR() const;
    unsigned char GetG() const;
    unsigned char GetB() const;
    std::string GetHexValue() const;
    std::string GetName() const;
};