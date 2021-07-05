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
int main() { //string fileToCopy = "..\\input\\layer1.tga";
    ImageProcessingTGA imageProcessor;
    /*
    imageProcessor.readInFileTGA("src\\test.tga");
    cout << "the header #############################  THIs work" << endl;
    ImageProcessingTGA::HeaderTGA y = *imageProcessor.getPicture(0).header;
    imageProcessor.writeFileTGA(imageProcessor.getPicture(0));
    cout << "Commence test" << endl;
    imageProcessor.testPictures("writeTest.tga", "src\\test.tga"); 

    char a = (char)72;
    char b = (char)72;
    char c = (char)20;
    char d = (char)((((float)a / 255) * ((float)b / 255)) * 255);
    cout << "a " << a << " b " << b << " c " << c << " result " << d << endl;
    */

    // PART 1 ##############################################
    imageProcessor.readInFileTGA("input\\Layer1.tga");
    imageProcessor.writeFileTGA(imageProcessor.getPicture(0), "layer1.tga");
    cout << "Success 1" << endl;
    imageProcessor.readInFileTGA("input\\pattern1.tga");
    imageProcessor.writeFileTGA(imageProcessor.getPicture(1), "pattern1.tga");
    cout << "Success 2" << endl;
    imageProcessor.multiply(imageProcessor.getPicture(0), imageProcessor.getPicture(1));
    cout << "Success 3" << endl;
    imageProcessor.writeFileTGA(imageProcessor.getPicture(2), "part1.tga");
    imageProcessor.testPictures("output\\part1.tga", "examples\\EXAMPLE_part1.tga");
    
    // PART 2 #############################################





    //imageProcessor.writeMonoDEBUG(imageProcessor.getPicture(0));
    //imageProcessor.readInFileTGA("oneColor.tga");

    return 0;
}