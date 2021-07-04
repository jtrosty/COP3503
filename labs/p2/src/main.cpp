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
    cout << "the header #############################" << endl;
    imageProcessor.printHeader(*(imageProcessor.getPicture(0).header));
    cout << "mono debug #############################" << endl;
    imageProcessor.writeMonoDEBUG(imageProcessor.getPicture(0));
    imageProcessor.readInFileTGA("oneColor.tga");

    return 0;
}