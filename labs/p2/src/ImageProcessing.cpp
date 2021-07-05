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
    fileInput.open(fileName, ios_base::in |ios_base::binary);
    if (fileInput.is_open()) {
        cout << "File is open" << endl;
        // Reads in the header
        fileInput.read((char*)&fileHeaderData->idLength,        sizeof(fileHeaderData->idLength));
        fileInput.read((char*)&fileHeaderData->colorMapType,    sizeof(fileHeaderData->colorMapType));
        fileInput.read((char*)&fileHeaderData->dataTypeCode,    sizeof(fileHeaderData->dataTypeCode));
        fileInput.read((char*)&fileHeaderData->colorMapOrigin,  sizeof(fileHeaderData->colorMapOrigin));
        fileInput.read((char*)&fileHeaderData->colorMapLength,  sizeof(fileHeaderData->colorMapLength));
        fileInput.read((char*)&fileHeaderData->colorMapDepth,   sizeof(fileHeaderData->colorMapDepth));
        fileInput.read((char*)&fileHeaderData->xOrigin,         sizeof(fileHeaderData->xOrigin));
        fileInput.read((char*)&fileHeaderData->yOrigin,         sizeof(fileHeaderData->yOrigin));
        fileInput.read((char*)&fileHeaderData->width,           sizeof(fileHeaderData->width));
        fileInput.read((char*)&fileHeaderData->height,          sizeof(fileHeaderData->height));
        fileInput.read((char*)&fileHeaderData->bitsPerPixel,    sizeof(fileHeaderData->bitsPerPixel));
        fileInput.read((char*)&fileHeaderData->imageDescriptor, sizeof(fileHeaderData->imageDescriptor));

        printHeader(*fileHeaderData);

        // Read In the pixels of the file. 
        int size = (fileHeaderData->width) * (fileHeaderData->height);
        cout << "Size is: " << size << endl;
        Pixel* pixelData = new Pixel[size];

        for (int i = 0; i < size; i++) {
            fileInput.read((char*)&pixelData[i].blue, sizeof(unsigned char));
            fileInput.read((char*)&pixelData[i].green, sizeof(unsigned char));
            fileInput.read((char*)&pixelData[i].red, sizeof(unsigned char));
        }
        
        cout << "finsihed read of pixel data" << endl;
        
        Picture* picture = new Picture;
        picture->header = fileHeaderData;
        picture->pixelData = pixelData;
        picture->lengthOfPixelData = new int(size);

        pictures.push_back(picture);
        cout << "################# pictures #######################" << endl;
        printHeader(*pictures.at(0)->header);

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
    fileOutput.open("writeTest.tga", ios_base::binary |ios_base::out);
    if(fileOutput.is_open()) {

        cout << "Commence wite of Header: " << endl;
        fileOutput.write((char *)&picture.header->idLength,        sizeof(picture.header->idLength));
        fileOutput.write((char *)&picture.header->colorMapType,    sizeof(picture.header->colorMapType));
        fileOutput.write((char *)&picture.header->dataTypeCode,    sizeof(picture.header->dataTypeCode));
        fileOutput.write((char *)&picture.header->colorMapOrigin,  sizeof(picture.header->colorMapOrigin));
        fileOutput.write((char *)&picture.header->colorMapLength,  sizeof(picture.header->colorMapLength));
        fileOutput.write((char *)&picture.header->colorMapDepth,   sizeof(picture.header->colorMapDepth));
        fileOutput.write((char *)&picture.header->xOrigin,         sizeof(picture.header->xOrigin));
        fileOutput.write((char *)&picture.header->yOrigin,         sizeof(picture.header->yOrigin));
        fileOutput.write((char *)&picture.header->width,           sizeof(picture.header->width));
        fileOutput.write((char *)&picture.header->height,          sizeof(picture.header->height));
        fileOutput.write((char *)&picture.header->bitsPerPixel,    sizeof(picture.header->bitsPerPixel));
        fileOutput.write((char *)&picture.header->imageDescriptor, sizeof(picture.header->imageDescriptor));

        cout << "Commence write of pixels: " << endl;
        cout << "Lenght is: " << *picture.lengthOfPixelData << endl;
        for (int i = 0; i < *(picture.lengthOfPixelData); i++) {
            //cout << i << " ";
            fileOutput.write((char *)&picture.pixelData[i].blue,  sizeof(unsigned char));
            fileOutput.write((char *)&picture.pixelData[i].green, sizeof(unsigned char));
            fileOutput.write((char *)&picture.pixelData[i].red,   sizeof(unsigned char));
        }
        fileOutput.close();
    }
    else {
        cout << "Ouptut file did not open" << endl;
    }
}

void ImageProcessingTGA::writeMonoDEBUG(Picture& picture) {
    fileOutput.open("oneColor.tga", ios_base::binary |ios_base::out);
    if(fileOutput.is_open()) {

        cout << "Commence wite of Header: " << endl;
        fileOutput.write((char*)&picture.header->idLength,        sizeof(picture.header->idLength));
        fileOutput.write((char*)&picture.header->colorMapType,    sizeof(picture.header->colorMapType));
        fileOutput.write((char*)&picture.header->dataTypeCode,    sizeof(picture.header->dataTypeCode));
        fileOutput.write((char*)&picture.header->colorMapOrigin,  sizeof(picture.header->colorMapOrigin));
        fileOutput.write((char*)&picture.header->colorMapLength,  sizeof(picture.header->colorMapLength));
        fileOutput.write((char*)&picture.header->colorMapDepth,   sizeof(picture.header->colorMapDepth));
        fileOutput.write((char*)&picture.header->xOrigin,         sizeof(picture.header->xOrigin));
        fileOutput.write((char*)&picture.header->yOrigin,         sizeof(picture.header->yOrigin));
        fileOutput.write((char*)&picture.header->width,           sizeof(picture.header->width));
        fileOutput.write((char*)&picture.header->height,          sizeof(picture.header->height));
        fileOutput.write((char*)&picture.header->bitsPerPixel,    sizeof(picture.header->bitsPerPixel));
        fileOutput.write((char*)&picture.header->imageDescriptor, sizeof(picture.header->imageDescriptor));

        cout << "Commence write of pixels: " << endl;
        cout << "Length is: " << *picture.lengthOfPixelData << endl;
        char color = (char)98;

        for (int i = 0; i < *(picture.lengthOfPixelData); i++) {
            //cout << i << " ";
            fileOutput.write(&color, sizeof(unsigned char));
            fileOutput.write(&color, sizeof(unsigned char));
            fileOutput.write(&color, sizeof(unsigned char));
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
 int ImageProcessingTGA::testPictures(char* lhs, char* rhs) {
    ifstream fileRhs;
    fileInput.open(lhs, ios_base::binary | ios_base::in);
    fileRhs.open(rhs, ios_base::binary | ios_base::in);
    if (fileInput && fileRhs) {

        // Length of LHS file
        fileInput.seekg(0, fileInput.end);
        int lengthLhs = fileInput.tellg();
        fileInput.seekg(0, fileInput.beg);

        // Lenght of RHS file 
        fileRhs.seekg(0, fileRhs.end);
        int lengthRhs = fileRhs.tellg();
        fileRhs.seekg(0, fileRhs.beg);
        cout << "Files size. LHS size: " << lengthLhs << " RHS: " << lengthRhs << endl;

        if (lengthLhs == lengthRhs) {
            char* lhsByte = new char;
            char* rhsByte = new char;
            for (int i = 0; i < lengthLhs; i++) {
                fileInput.read(lhsByte, sizeof(char));
                fileRhs.read(rhsByte, sizeof(char));
                if (*lhsByte == *rhsByte) continue;
                else {
                    cout << "The files are not equivalent. Counter: " << i << endl;
                    cout << "LHS " << *lhsByte << " RHS: " << *rhsByte << endl;
                    delete lhsByte;
                    delete rhsByte;
                    return 0; // return 0 for failure
                }
            }
            delete lhsByte;
            delete rhsByte;
        }
        else {
            cout << "Files are not the same size. LHS size: " << lengthLhs << " RHS: " << lengthRhs << endl;
        }
    }
    else {
        cout << "Files did not open properly. Check filename and location." << endl;
    }
    // Return 1 for success
    cout << "Test Passsed, both files are the same" << endl;

    return 1;
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

/**************************************************************
 * ************************ Print Behavior ********************
 * ************************************************************/
void ImageProcessingTGA::printHeader(HeaderTGA& header) {
    cout << "idLenght: " << (int)header.idLength << endl;
    cout << "colorMapType: " << (int)header.colorMapType << endl;
    cout << "dataTypeCode: " << (int)header.dataTypeCode << endl;
    cout << "colorMapOrigin: " << header.colorMapOrigin << endl;
    cout << "colorMapLenght: " << header.colorMapLength << endl;
    cout << "colorMapDepth: " << (int)header.colorMapDepth << endl;
    cout << "x Origin: " << header.xOrigin << endl;
    cout << "y Origin: " << header.yOrigin << endl;
    cout << "width: " << header.width << endl;
    cout << "height: " << header.height << endl;
    cout << "bitsPerPixedl: " << (int)header.bitsPerPixel << endl;
    cout << "imageDescriptor: " << (int)header.imageDescriptor << endl;
}