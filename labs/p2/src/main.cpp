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
    imageProcessor.readInFileTGA("test.tga");
    imageProcessor.writeFileTGA(imageProcessor.getPicture(0));

    return 0;
}