#include <iostream>
#include <string>
#include <map>
using namespace std;

//////////////////////////////////////////////////////////////
//            Sets and Maps 10.2.5      

string findTheDigits(string x, string y) {
	// Write your code here
    map<char, int> additionalDigits;
    map<char, int>::iterator iter;

    char ASCII0 = 48;
    for (char i = ASCII0; i <= ASCII0 + 9; i++) {
        additionalDigits.emplace(i, 0);
    }

    for (int i = 0; i < y.size(); i++) {
        additionalDigits.at(y.at(i))++;
    }

    for (int i = 0; i < x.size(); i++) {
        additionalDigits.at(x.at(i))--;
    }

    string result;

    for (iter = additionalDigits.begin(); iter != additionalDigits.end(); iter++) {
        for (int i = 0; i < iter->second; i++) result.push_back(iter->first);
    }
    
	return result;
}

int main(void) {
    string x = "1234";
    string y = "1234512";
    cout << findTheDigits(x, y);
    cout << endl;
    return 0;
}