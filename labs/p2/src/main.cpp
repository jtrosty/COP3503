#include <iostream>
#include <fstream>
#include <string.h>

#include "ImageProcessing.h"

using std::ifstream;
using std::ios_base;
using std::string;
using std::cout;
using std::endl;
using std::cin;

//#include "leaker.h"

int main() {
    //string fileToCopy = "..\\input\\layer1.tga";
    ImageProcessingTGA imageProcessor;
    ifstream testIn;
    testIn.open("test.tga", ios_base::in | ios_base::binary);
    if (testIn.is_open()) {
        cout << "This worked" << endl;
    }
    else {
        cout << "MAIN did not open" << endl;
    }

    cout << imageProcessor.readInFileTGA("test.tga") << endl;
    imageProcessor.writeFileTGA(imageProcessor.getPicture(0));

    return 0;
}