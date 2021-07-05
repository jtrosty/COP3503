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
   13. part5.tga
   14. part6.tga
   15. part7.tga
   16. part8_r.tga
   17. part8_g.tga
   18. part8_b.tga
   19. layer_red.tga
   20. layer_green.tga
   21. layer_blue.tga
   22. part9.tga
   23. text2.tga
   24. part10.tga
   25. extracredit.tga
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

    // PART 5 #############################################
    cout << "Begin Part 5 ####################################################" << endl;
    imageProcessor.overlay(imageProcessor.getPicture(0), imageProcessor.getPicture(1));
    imageProcessor.writeFileTGA(imageProcessor.getPicture(13), "part5.tga");
    imageProcessor.testPictures("part5.tga", "examples\\EXAMPLE_part5.tga");

    // PART 6 #############################################
    cout << "Begin Part 6 ####################################################" << endl;
    imageProcessor.addAdjustRGB(imageProcessor.getPicture(4), 0, 200, 0);
    imageProcessor.writeFileTGA(imageProcessor.getPicture(14), "part6.tga");
    imageProcessor.testPictures("part6.tga", "examples\\EXAMPLE_part6.tga");

    // PART 7 #############################################
    cout << "Begin Part 7 ####################################################" << endl;
    imageProcessor.scaleAdjustRGB(imageProcessor.getPicture(4), 4.0f, 1.0f, 0.0f);
    imageProcessor.writeFileTGA(imageProcessor.getPicture(15), "part7.tga");
    imageProcessor.testPictures("part7.tga", "examples\\EXAMPLE_part7.tga");

    // PART 8 #############################################
    cout << "Begin Part 8 ####################################################" << endl;
    imageProcessor.individualChannel(imageProcessor.getPicture(4), 'r');
    imageProcessor.individualChannel(imageProcessor.getPicture(4), 'g');
    imageProcessor.individualChannel(imageProcessor.getPicture(4), 'b');
    imageProcessor.writeFileTGA(imageProcessor.getPicture(16), "part8_r.tga");
    imageProcessor.writeFileTGA(imageProcessor.getPicture(17), "part8_g.tga");
    imageProcessor.writeFileTGA(imageProcessor.getPicture(18), "part8_b.tga");
    imageProcessor.testPictures("part8_r.tga", "examples\\EXAMPLE_part8_r.tga");
    imageProcessor.testPictures("part8_g.tga", "examples\\EXAMPLE_part8_g.tga");
    imageProcessor.testPictures("part8_b.tga", "examples\\EXAMPLE_part8_b.tga");

    // PART 9 #############################################
    cout << "Begin Part 9 ####################################################" << endl;
    imageProcessor.readInFileTGA("input\\Layer_red.tga");
    imageProcessor.readInFileTGA("input\\Layer_green.tga");
    imageProcessor.readInFileTGA("input\\Layer_blue.tga");
    imageProcessor.combinePicsEachOneChannel(imageProcessor.getPicture(19), imageProcessor.getPicture(20), imageProcessor.getPicture(21));
    imageProcessor.writeFileTGA(imageProcessor.getPicture(22), "part9.tga");
    imageProcessor.testPictures("part9.tga", "examples\\EXAMPLE_part9.tga");

    // PART 10 #############################################
    cout << "Begin Part 10 ####################################################" << endl;
    cout << "size of picture " << imageProcessor.pictures.size() << endl;
    
    imageProcessor.readInFileTGA("input\\text2.tga");
    imageProcessor.rotate180(imageProcessor.getPicture(23));
    imageProcessor.writeFileTGA(imageProcessor.getPicture(24), "part10.tga");
    imageProcessor.testPictures("part10.tga", "examples\\EXAMPLE_part10.tga");

    // PART EXTRA CREDIT #############################################
    cout << "Begin Extra Credit ####################################################" << endl;
    
    cout << "size of picture " << imageProcessor.pictures.size() << endl;
    imageProcessor.extraCreditCombine4Pics(imageProcessor.getPicture(4), imageProcessor.getPicture(10), imageProcessor.getPicture(7), imageProcessor.getPicture(1));
    imageProcessor.writeFileTGA(imageProcessor.getPicture(25), "extracredit.tga");
    imageProcessor.testPictures("extracredit.tga", "examples\\EXAMPLE_extracredit.tga");
    cout << "size of picture " << imageProcessor.pictures.size() << endl;


    return 0;
}