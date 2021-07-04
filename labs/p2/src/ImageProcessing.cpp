#include "ImageProcessing.h"
//#include "leaker.h"

/**************************************************************
 * ********** Constructor/Copy Assignment/Destructor **********
 * ************************************************************/

// Constructor
ImageProcessingTGA::ImageProcessingTGA() {
    ifstream fileInput;
    ofstream fileOutput;
}

// Destructor
ImageProcessingTGA::~ImageProcessingTGA() {
    int size = pictures.size();
    for (int i = 0; i < size; i++) {
        delete[] pictures.at(i)->pixelData;
        delete pictures.at(i)->header;
        delete pictures.at(i)->lengthOfPixelData;
        delete pictures.at(i);
    }
}

/**************************************************************
 * ************** Read In Behaviour ***************************
 * ************************************************************/

char ImageProcessingTGA::readInFileTGA(char* fileName) {
    HeaderTGA* fileHeaderData = new HeaderTGA;
    fileInput.open(fileName, ios_base::binary);
    if (fileInput.is_open()) {
        cout << "File open" << endl; 
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
        picture->lengthOfPixelData = new int(size);

        pictures.push_back(picture);

        fileInput.close();
        return 'S';
    }
    else {
        cout << "file is not open" << endl;
        return 'F';
    }
}


/**************************************************************
 * ************** Write Out Behaviour *************************
 * ************************************************************/

void ImageProcessingTGA::writeFileTGA(Picture& picture) {
    fileOutput.open("writeTest.tga", ios_base::binary);
    if(fileOutput.is_open()) {

        cout << "Commence wite of Header: " << endl;
        fileOutput.write(&picture.header->idLength,              sizeof(picture.header->idLength));
        fileOutput.write(&picture.header->colorMapType,          sizeof(picture.header->colorMapType));
        fileOutput.write(&picture.header->dataTypeCode,          sizeof(picture.header->dataTypeCode));
        fileOutput.write((char*)&picture.header->colorMapOrigin, sizeof(picture.header->colorMapOrigin));
        fileOutput.write((char*)&picture.header->colorMapLength, sizeof(picture.header->colorMapLength));
        fileOutput.write(&picture.header->colorMapDepth,         sizeof(picture.header->colorMapDepth));
        fileOutput.write((char*)&picture.header->xOrigin,        sizeof(picture.header->xOrigin));
        fileOutput.write((char*)&picture.header->yOrigin,        sizeof(picture.header->yOrigin));
        fileOutput.write((char*)&picture.header->width,          sizeof(picture.header->width));
        fileOutput.write((char*)&picture.header->height,         sizeof(picture.header->height));
        fileOutput.write(&picture.header->bitsPerPixel,          sizeof(picture.header->bitsPerPixel));
        fileOutput.write(&picture.header->imageDescriptor,       sizeof(picture.header->imageDescriptor));

        cout << "Commence wite of pixels: " << endl;
        cout << "Lenght is: " << *(picture.lengthOfPixelData) << endl;
        for (int i = 0; i < *(picture.lengthOfPixelData); i++) {
            fileOutput.write((char*)picture.pixelData[i].blue, sizeof(picture.pixelData));
            fileOutput.write((char*)picture.pixelData[i].green, sizeof(picture.pixelData));
            fileOutput.write((char*)picture.pixelData[i].red, sizeof(picture.pixelData));
        }
        fileOutput.close();
    }
    else {
        cout << "Ouptut file did not open" << endl;
    }
}

/**************************************************************
 * ************************ Accessors *************************
 * ************************************************************/
ImageProcessingTGA::Picture& ImageProcessingTGA::getPicture(int element) {
    if (element >= pictures.size()) {
        cout << "No picture at that element." << endl;
    }
    return *(pictures.at(element));
}
