#include <iostream>
#include <fstream>
#include <string.h>

using std::ifstream;
using std::ios_base;
using std::string;
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
    
    ifstream fileInput;

    public:
    // constructor
    ImageProcessingTGA() {
    }

    void readInFileTGA(string file);
    
};