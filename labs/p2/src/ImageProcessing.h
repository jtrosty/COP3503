#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>

using std::ifstream;
using std::ofstream;
using std::ios_base;
using std::string;
using std::vector;
using std::cout;
using std::endl;
using std::boolalpha;

//#include "leaker.h"

class ImageProcessingTGA {

    public:
    struct HeaderTGA {
        char idLength;
        char colorMapType;
        char dataTypeCode;
        short colorMapOrigin;
        short colorMapLength;
        char colorMapDepth;
        short xOrigin;
        short yOrigin;
        short width;
        short height;
        char bitsPerPixel;
        char imageDescriptor;
    };

    struct Pixel {
        unsigned char blue;
        unsigned char green;
        unsigned char red;
    };

    struct Picture {
        HeaderTGA* header;
        Pixel* pixelData;
        int* lengthOfPixelData;
    };
    
    ifstream fileInput;
    ofstream fileOutput;
    vector<Picture*> pictures;

    // constructor
    ImageProcessingTGA();

    // Destructor
    ~ImageProcessingTGA();

    // Read in behaviour
    char readInFileTGA(char* fileName);

    // Writing behavior
    void writeFileTGA(Picture& picture, char* title);
    void writeMonoDEBUG(Picture& picture);

    // Blend Behavior
    void multiply(Picture& lhs, Picture& rhs);
    void subtract(Picture& lhs, Picture& rhs);
    void screen(Picture& lhs, Picture& rhs);
    void overlay(Picture& lhs, Picture& rhs);
    void addAdjustRGB(Picture& pic, unsigned char r, unsigned char g, unsigned char b);
    void scaleAdjustRGB(Picture& pic, float r, float g, float b);
    void individualChannel(Picture& pic, char channel);
    void combinePicsEachOneChannel(Picture& red, Picture& green, Picture& blue);
    void rotate180(Picture& pic);
    void extraCreditCombine4Pics(Picture& topLeft, Picture& topRight, Picture& bottomLeft, Picture& bottomRight);

    // Testing Function
    int testPictures(char* lhs, char* rhs);

    // Accessors
    Picture& getPicture(int element);

    // Printing Behaviour 
    void printHeader(HeaderTGA& header); 

    // Helper math functions
    unsigned char clampSubtractChar(unsigned char& lhs, unsigned char& rhs);
    unsigned char clampAddChar(unsigned char& lhs, unsigned char& rhs);
    unsigned char clampScaleChar(unsigned char& color, float& scale);

    
};