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
    void writeFileTGA(Picture& picture);
    void writeMonoDEBUG(Picture& picture);

    // Testing Function

    // Accessors
    Picture& getPicture(int element);

    // Printing Behaviour 
    void printHeader(HeaderTGA& header); 

    
};