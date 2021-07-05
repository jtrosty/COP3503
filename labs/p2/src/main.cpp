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

   /*
   0. layer1.tga
   1. patter1.tga
   2. part1.tga
   3. layer2.tga
   4. car.tga
   5. part2.tga
   6. pattern2.tga
   7. text.tga
   8. part3 int multiply
   9. part3.tga
   10. circle.tga
   11. part 4 int, multiply of 3 and 10
   12. part4.tga
   13.
   14.
   */


    // PART 1 ##############################################
    cout << "Part 1 Multiply ################################################" << endl;
    imageProcessor.readInFileTGA("input\\Layer1.tga");
    imageProcessor.readInFileTGA("input\\pattern1.tga");
    imageProcessor.multiply(imageProcessor.getPicture(0), imageProcessor.getPicture(1));
    imageProcessor.writeFileTGA(imageProcessor.getPicture(2), "part1.tga");
    imageProcessor.testPictures("part1.tga", "examples\\EXAMPLE_part1.tga");
    
    // PART 2 #############################################
    cout << "Begin Part 2 ####################################################" << endl;
    imageProcessor.readInFileTGA("input\\Layer2.tga");
    imageProcessor.readInFileTGA("input\\car.tga");
    imageProcessor.subtract(imageProcessor.getPicture(4), imageProcessor.getPicture(3));
    imageProcessor.writeFileTGA(imageProcessor.getPicture(5), "part2.tga");
    imageProcessor.testPictures("part2.tga", "examples\\EXAMPLE_part2.tga");

    // PART 3 #############################################
    cout << "Begin Part 3 ####################################################" << endl;
    imageProcessor.readInFileTGA("input\\pattern2.tga");
    imageProcessor.readInFileTGA("input\\text.tga");
    imageProcessor.multiply(imageProcessor.getPicture(0), imageProcessor.getPicture(6));
    imageProcessor.screen(imageProcessor.getPicture(8), imageProcessor.getPicture(7));
    imageProcessor.writeFileTGA(imageProcessor.getPicture(9), "part3.tga");
    imageProcessor.testPictures("part3.tga", "examples\\EXAMPLE_part3.tga");

    // PART 4 #############################################
    cout << "Begin Part 4 ####################################################" << endl;
    imageProcessor.readInFileTGA("input\\circles.tga");
    imageProcessor.multiply(imageProcessor.getPicture(3), imageProcessor.getPicture(10));
    imageProcessor.subtract(imageProcessor.getPicture(11), imageProcessor.getPicture(6));
    imageProcessor.writeFileTGA(imageProcessor.getPicture(12), "part4.tga");
    imageProcessor.testPictures("part4.tga", "examples\\EXAMPLE_part4.tga");


    //imageProcessor.writeMonoDEBUG(imageProcessor.getPicture(0));
    //imageProcessor.readInFileTGA("oneColor.tga");

    return 0;
}