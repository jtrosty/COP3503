#include <string>

using std::string;

class SolutionAtoi {
public:
    bool isRelaventInt(char input) {
        char plus = '+';
        char negative = '-';
        char decimal = '.';
        char zero = 30;
        char nine = 39;
        if (input <= nine ||
            input >= zero ||
            input == plus ||
            input == negative ||
            input == decimal) 
            return true;
        return false;
    }

    int myAtoi(string s) {
        char whitespace = ' ';
        char plus = '+';
        char negative = '-';
        char decimal = '.';


    }
};