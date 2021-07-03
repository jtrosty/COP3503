#include "ImageProcessing.h"

/**************************************************************
 * ************** Read In Behaviour ***************************
 * ************************************************************/

void ImageProcessingTGA::readInFileTGA(string file) {
    fileInput.open(file, ios_base::in);
    if (fileInput.is_open()) {
        cout << "File open" << endl; 
    }
    fileInput.read(&fileHeaderData.idLength, sizeof(fileHeaderData.idLength));
    fileInput.read(&fileHeaderData.colorMapType, sizeof(fileHeaderData.colorMapType));
    fileInput.read(&fileHeaderData.dataTypeCode, sizeof(fileHeaderData.dataTypeCode));
    fileInput.read((char*)&fileHeaderData.colorMapOrigin, sizeof(fileHeaderData.colorMapOrigin));
    fileInput.read((char*)&fileHeaderData.colorMapLength, sizeof(fileHeaderData.colorMapLength));
    fileInput.read(&fileHeaderData.colorMapDepth, sizeof(fileHeaderData.colorMapDepth));
    fileInput.read((char*)&fileHeaderData.xOrigin, sizeof(fileHeaderData.xOrigin));
    fileInput.read((char*)&fileHeaderData.yOrigin, sizeof(fileHeaderData.yOrigin));
    fileInput.read((char*)&fileHeaderData.width, sizeof(fileHeaderData.width));
    fileInput.read((char*)&fileHeaderData.height, sizeof(fileHeaderData.height));
    fileInput.read(&fileHeaderData.bitsPerPixel, sizeof(fileHeaderData.bitsPerPixel));
    fileInput.read(&fileHeaderData.imageDescriptor, sizeof(fileHeaderData.imageDescriptor));


}