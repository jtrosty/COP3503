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


int main() {
    cout << "Test complete" << endl;

    //string fileToCopy = "..\\input\\layer1.tga";
    ImageProcessingTGA imageProcessor;
    cout << imageProcessor.readInFileTGA("..\\input\\layer1.tga") << endl;


    return 0;
}