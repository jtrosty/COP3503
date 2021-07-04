#include "ImageProcessing.h"

/**************************************************************
 * ************** Read In Behaviour ***************************
 * ************************************************************/

void ImageProcessingTGA::readInFileTGA(string file) {

    HeaderTGA fileHeaderData;
    fileInput.open(file, ios_base::in);
    if (fileInput.is_open()) {
        cout << "File open" << endl; 
    }

    // Reads in the header
    fileInput.read(&fileHeaderData.idLength,              sizeof(fileHeaderData.idLength));
    fileInput.read(&fileHeaderData.colorMapType,          sizeof(fileHeaderData.colorMapType));
    fileInput.read(&fileHeaderData.dataTypeCode,          sizeof(fileHeaderData.dataTypeCode));
    fileInput.read((char*)&fileHeaderData.colorMapOrigin, sizeof(fileHeaderData.colorMapOrigin));
    fileInput.read((char*)&fileHeaderData.colorMapLength, sizeof(fileHeaderData.colorMapLength));
    fileInput.read(&fileHeaderData.colorMapDepth,         sizeof(fileHeaderData.colorMapDepth));
    fileInput.read((char*)&fileHeaderData.xOrigin,        sizeof(fileHeaderData.xOrigin));
    fileInput.read((char*)&fileHeaderData.yOrigin,        sizeof(fileHeaderData.yOrigin));
    fileInput.read((char*)&fileHeaderData.width,          sizeof(fileHeaderData.width));
    fileInput.read((char*)&fileHeaderData.height,         sizeof(fileHeaderData.height));
    fileInput.read(&fileHeaderData.bitsPerPixel,          sizeof(fileHeaderData.bitsPerPixel));
    fileInput.read(&fileHeaderData.imageDescriptor,       sizeof(fileHeaderData.imageDescriptor));

    // Read In the pixels of the file. 
    int size = fileHeaderData.width * fileHeaderData.height;
    Pixel* pixelData = new Pixel[size];

    for (int i = 0; i < size; i++) {
        fileInput.read((char*)pixelData[i].blue, sizeof(char));
        fileInput.read((char*)pixelData[i].green, sizeof(char));
        fileInput.read((char*)pixelData[i].red, sizeof(char));
    }
    
    Picture* picture = new Picture;
    picture->header = fileHeaderData;
    picture->pixelData = pixelData;

    pictures.push_back(picture);

    fileInput.close();
}


/**************************************************************
 * ************** Write Out Behaviour *************************
 * ************************************************************/

void ImageProcessingTGA::writeFileTGA(Picture& picture) {
    

}


