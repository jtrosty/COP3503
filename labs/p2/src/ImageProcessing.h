#include <iostream>
#include <fstream>
#include <string.h>
#include <vector>

using std::ifstream;
using std::ios_base;
using std::string;
using std::vector;
using std::cout;
using std::endl;

class ImageProcessingTGA {

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
        HeaderTGA header;
        Pixel* pixelData;
    };
    
    ifstream fileInput;
    vector<Picture*> pictures;

    public:
    // constructor
    ImageProcessingTGA();

    // Read in behaviour
    void readInFileTGA(string file);

    // Writing behavior
    void writeFileTGA(Picture& picture);


    // Testing Function

    
};