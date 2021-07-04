#include "ImageProcessing.h"
//#include "leaker.h"

/**************************************************************
 * ********** Constructor/Copy Assignment/Destructor **********
 * ************************************************************/

// Constructor
ImageProcessingTGA::ImageProcessingTGA() {}

// Destructor
ImageProcessingTGA::~ImageProcessingTGA() {
    int size = pictures.size();
    for (int i = 0; i < size; i++) {
        delete[] pictures.at(i)->pixelData;
        delete pictures.at(i)->header;
        delete pictures.at(i);
    }
}

/**************************************************************
 * ************** Read In Behaviour ***************************
 * ************************************************************/

char ImageProcessingTGA::readInFileTGA(string file) {
    HeaderTGA* fileHeaderData = new HeaderTGA;
    fileInput.open(file, ios_base::in);
    if (fileInput.is_open()) {
        cout << "File open" << endl; 
        return 'F';
    }

    // Reads in the header
    fileInput.read(&fileHeaderData->idLength,              sizeof(fileHeaderData->idLength));
    fileInput.read(&fileHeaderData->colorMapType,          sizeof(fileHeaderData->colorMapType));
    fileInput.read(&fileHeaderData->dataTypeCode,          sizeof(fileHeaderData->dataTypeCode));
    fileInput.read((char*)&fileHeaderData->colorMapOrigin, sizeof(fileHeaderData->colorMapOrigin));
    fileInput.read((char*)&fileHeaderData->colorMapLength, sizeof(fileHeaderData->colorMapLength));
    fileInput.read(&fileHeaderData->colorMapDepth,         sizeof(fileHeaderData->colorMapDepth));
    fileInput.read((char*)&fileHeaderData->xOrigin,        sizeof(fileHeaderData->xOrigin));
    fileInput.read((char*)&fileHeaderData->yOrigin,        sizeof(fileHeaderData->yOrigin));
    fileInput.read((char*)&fileHeaderData->width,          sizeof(fileHeaderData->width));
    fileInput.read((char*)&fileHeaderData->height,         sizeof(fileHeaderData->height));
    fileInput.read(&fileHeaderData->bitsPerPixel,          sizeof(fileHeaderData->bitsPerPixel));
    fileInput.read(&fileHeaderData->imageDescriptor,       sizeof(fileHeaderData->imageDescriptor));

    // Read In the pixels of the file. 
    int size = (fileHeaderData->width) * (fileHeaderData->height);
    Pixel* pixelData = new Pixel[size];

    for (int i = 0; i < size; i++) {
        fileInput.read((char*)pixelData[i].blue, sizeof(unsigned char));
        fileInput.read((char*)pixelData[i].green, sizeof(unsigned char));
        fileInput.read((char*)pixelData[i].red, sizeof(unsigned char));
    }
    
    Picture* picture = new Picture;
    picture->header = fileHeaderData;
    picture->pixelData = pixelData;

    pictures.push_back(picture);

    fileInput.close();
    return 'S';
}


/**************************************************************
 * ************** Write Out Behaviour *************************
 * ************************************************************/

void ImageProcessingTGA::writeFileTGA(Picture& picture) {
    fileOutput.open("..\\output\\Test.tga", ios_base::binary);
    char* startAddress = (char*)picture.header->idLength;
    fileOutput.write(startAddress, sizeof(HeaderTGA));
    char* startPixels = (char*)picture.pixelData[0].blue;
    fileOutput.write(startPixels, sizeof(picture.pixelData));
}

/**************************************************************
 * ************************ Accessors *************************
 * ************************************************************/
ImageProcessingTGA::Picture& ImageProcessingTGA::getPicture(int element) {
    return *(pictures.at(element));
}
