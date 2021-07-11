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

// Copy Contrucutor
ImageProcessingTGA::ImageProcessingTGA(const ImageProcessingTGA& rhs) {
    int size = rhs.pictures.size();
    for (int i = 0; i < size; i++) {
        HeaderTGA* newHeader = new HeaderTGA;
        ImageProcessingTGA::copyHeader(newHeader, rhs.pictures.at(i)->header);
        /*
        newHeader->idLength = rhs.pictures.at(i)->header->idLength;
        newHeader->colorMapType = rhs.pictures.at(i)->header->colorMapType;
        newHeader->dataTypeCode = rhs.pictures.at(i)->header->colorMapType;
        newHeader->colorMapOrigin = rhs.pictures.at(i)->header->colorMapOrigin;
        newHeader->colorMapLength = rhs.pictures.at(i)->header->colorMapLength;
        newHeader->colorMapDepth = rhs.pictures.at(i)->header->colorMapDepth;
        newHeader->xOrigin = rhs.pictures.at(i)->header->xOrigin;
        newHeader->yOrigin = rhs.pictures.at(i)->header->yOrigin;
        newHeader->width = rhs.pictures.at(i)->header->width;
        newHeader->height = rhs.pictures.at(i)->header->height;
        newHeader->bitsPerPixel = rhs.pictures.at(i)->header->bitsPerPixel;
        newHeader->imageDescriptor = rhs.pictures.at(i)->header->imageDescriptor;
        */

        int* newLengthOfPixel = new int(*rhs.pictures.at(i)->lengthOfPixelData);
        Pixel* newPixelData = new Pixel[*newLengthOfPixel];

        for (int j = 0; j < *newLengthOfPixel; j++) {
            newPixelData[j] = rhs.pictures.at(i)->pixelData[j];
        }
        this->pictures.at(i)->header = newHeader;
        this->pictures.at(i)->lengthOfPixelData = newLengthOfPixel;
        this->pictures.at(i)->pixelData = newPixelData;
    }
}

// Copy Assignment overload
ImageProcessingTGA& ImageProcessingTGA::operator=(const ImageProcessingTGA& rhs) {
    int size = rhs.pictures.size();
    for (int i = 0; i < size; i++) {
        HeaderTGA* newHeader = new HeaderTGA;
        ImageProcessingTGA::copyHeader(newHeader, rhs.pictures.at(i)->header);

        int* newLengthOfPixel = new int(*rhs.pictures.at(i)->lengthOfPixelData);
        Pixel* newPixelDatat = new Pixel[*newLengthOfPixel];

        for (int j = 0; j < *newLengthOfPixel; j++) {
            newPixelDatat[j] = rhs.pictures.at(i)->pixelData[j];
        }
        this->pictures.at(i)->header = newHeader;
        this->pictures.at(i)->lengthOfPixelData = newLengthOfPixel;
        this->pictures.at(i)->pixelData = newPixelDatat;
    }
    return *this;
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

        // Read In the pixels of the file. 
        int size = (fileHeaderData->width) * (fileHeaderData->height);
        Pixel* pixelData = new Pixel[size];

        for (int i = 0; i < size; i++) {
            fileInput.read((char*)&pixelData[i].blue, sizeof(unsigned char));
            fileInput.read((char*)&pixelData[i].green, sizeof(unsigned char));
            fileInput.read((char*)&pixelData[i].red, sizeof(unsigned char));
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

void ImageProcessingTGA::writeFileTGA(Picture& picture, char* title) {

    fileOutput.open(title, ios_base::binary |ios_base::out);
    if(fileOutput.is_open()) {

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
 * ********************* Blend Behaviour **********************
 * ************************************************************/

// CODE ASSUMES BOTH PICTURES HAVE SAME SIZE ADN WIDTH.
void ImageProcessingTGA::multiply(Picture& lhs, Picture& rhs) {
    
    Picture* result = new Picture;
    int lengthLhs = *lhs.lengthOfPixelData;
    int isSameLength = 0;
    int longest = 0;
    int shortest = 0;
    const float SIZEBYTE = 255.0f;
    const float ROUND = 0.5f;

    if (*lhs.lengthOfPixelData == *rhs.lengthOfPixelData) {
        HeaderTGA* newHeader = new HeaderTGA;
        copyHeader(newHeader, lhs.header);
        result->header = newHeader;
        int* newLength = new int(*lhs.lengthOfPixelData);
        result->lengthOfPixelData = newLength;
        longest = *lhs.lengthOfPixelData;
        isSameLength = 0;
    }
    else if (*lhs.lengthOfPixelData > *rhs.lengthOfPixelData) {
        // Logic if the size is not the same and lhs is bigger
    }
    else {
        // TODO possible future make it so it can take pictures of different sizes.
    }
    if (isSameLength == 0) {
        Pixel* resultPixels = new Pixel[*result->lengthOfPixelData];
        float x = 0.0f;
        float y = 0.0f;

        for (int i = 0; i < longest; i++) {
            // Blue
            x = ((float)lhs.pixelData[i].blue  / SIZEBYTE);
            y = ((float)rhs.pixelData[i].blue  / SIZEBYTE);
            resultPixels[i].blue =  (unsigned char)(((x * y) * SIZEBYTE) + ROUND);
            // Green
            x = ((float)lhs.pixelData[i].green  / SIZEBYTE);
            y = ((float)rhs.pixelData[i].green  / SIZEBYTE);
            resultPixels[i].green = (unsigned char)(((x * y) * SIZEBYTE) + ROUND);
            // Red
            x = ((float)lhs.pixelData[i].red  / SIZEBYTE);
            y = ((float)rhs.pixelData[i].red  / SIZEBYTE);
            resultPixels[i].red =   (unsigned char)(((x * y) * SIZEBYTE) + ROUND);
        }
        result->pixelData = resultPixels;
    }
    pictures.push_back(result);
}

void ImageProcessingTGA::subtract(Picture& lhs, Picture& rhs) {
    Picture* result = new Picture;
    int lengthLhs = *lhs.lengthOfPixelData;
    int isSameLength = 0;
    int longest = 0;
    int shortest = 0;

    if (*lhs.lengthOfPixelData == *rhs.lengthOfPixelData) {
        HeaderTGA* newHeader = new HeaderTGA;
        copyHeader(newHeader, lhs.header);
        result->header = newHeader;
        result->lengthOfPixelData = new int(*lhs.lengthOfPixelData);
        longest = *lhs.lengthOfPixelData;
        isSameLength = 0;
    }
    else if (*lhs.lengthOfPixelData > *rhs.lengthOfPixelData) {
        // Logic if the size is not the same and lhs is bigger
    }
    else {
        // Logic if the size is not the same and rhs is bigger
    }
    if (isSameLength == 0) {
        Pixel* resultPixels = new Pixel[*result->lengthOfPixelData];
        float x = 0.0f;
        float y = 0.0f;

        for (int i = 0; i < longest; i++) {
            // Blue
            resultPixels[i].blue =  clampSubtractChar(lhs.pixelData[i].blue, rhs.pixelData[i].blue);
            // Green
            resultPixels[i].green = clampSubtractChar(lhs.pixelData[i].green, rhs.pixelData[i].green);
            // Red
            resultPixels[i].red =  clampSubtractChar(lhs.pixelData[i].red, rhs.pixelData[i].red);
        }
        result->pixelData = resultPixels;
    }
    pictures.push_back(result);

}

void ImageProcessingTGA::screen(Picture& lhs, Picture& rhs) {
    Picture* result = new Picture;
    int lengthLhs = *lhs.lengthOfPixelData;
    int isSameLength = 0;
    int longest = 0;
    int shortest = 0;
    const float SIZEBYTE = 255.0f;
    const float ROUND = 0.5f;

    if (*lhs.lengthOfPixelData == *rhs.lengthOfPixelData) {
        HeaderTGA* newHeader = new HeaderTGA;
        copyHeader(newHeader, lhs.header);
        result->header = newHeader;
        result->lengthOfPixelData = new int(*lhs.lengthOfPixelData);
        longest = *lhs.lengthOfPixelData;
        isSameLength = 0;
    }
    else if (*lhs.lengthOfPixelData > *rhs.lengthOfPixelData) {
        // Logic if the size is not the same and lhs is bigger
    }
    else {
        // Logic if the size is not the same and rhs is bigger
    }
    if (isSameLength == 0) {
        Pixel* resultPixels = new Pixel[*result->lengthOfPixelData];
        float x = 0.0f;
        float y = 0.0f;

        for (int i = 0; i < longest; i++) {
            // Blue
            x = ((float)lhs.pixelData[i].blue / SIZEBYTE);
            y = ((float)rhs.pixelData[i].blue / SIZEBYTE);
            resultPixels[i].blue =  (unsigned char)(((1 - (1 - x) * (1 -y)) * SIZEBYTE) + ROUND);
            // Green
            x = ((float)lhs.pixelData[i].green / SIZEBYTE);
            y = ((float)rhs.pixelData[i].green / SIZEBYTE);
            resultPixels[i].green =  (unsigned char)(((1 - (1 - x) * (1 -y)) * SIZEBYTE) + ROUND);
            // Red
            x = ((float)lhs.pixelData[i].red  / SIZEBYTE);
            y = ((float)rhs.pixelData[i].red  / SIZEBYTE);
            resultPixels[i].red =  (unsigned char)(((1 - (1 - x) * (1 -y)) * SIZEBYTE) + ROUND);
        }
        result->pixelData = resultPixels;
    }
    pictures.push_back(result);
}

void ImageProcessingTGA::overlay(Picture& lhs, Picture& rhs) {
    
    Picture* result = new Picture;
    int lengthLhs = *lhs.lengthOfPixelData;
    int isSameLength = 0;
    int longest = 0;
    int shortest = 0;
    const float SIZEBYTE = 255.0f;
    const float ROUND = 0.5f;

    if (*lhs.lengthOfPixelData == *rhs.lengthOfPixelData) {
        HeaderTGA* newHeader = new HeaderTGA;
        copyHeader(newHeader, lhs.header);
        result->header = newHeader;
        result->lengthOfPixelData = new int(*lhs.lengthOfPixelData);
        longest = *lhs.lengthOfPixelData;
        isSameLength = 0;
    }
    else if (*lhs.lengthOfPixelData > *rhs.lengthOfPixelData) {
        // Logic if the size is not the same and lhs is bigger
    }
    else {
        // Logic if the size is not the same and rhs is bigger
    }
    if (isSameLength == 0) {
        Pixel* resultPixels = new Pixel[*result->lengthOfPixelData];
        float x = 0.0f;
        float y = 0.0f;

        for (int i = 0; i < longest; i++) {
            // Blue
            x = ((float)lhs.pixelData[i].blue  / SIZEBYTE);
            y = ((float)rhs.pixelData[i].blue  / SIZEBYTE);
            if (y < 0.5f) {
                resultPixels[i].blue =  (unsigned char)(((2.0f * x * y) * SIZEBYTE) + ROUND);
            }
            else {
                resultPixels[i].blue =  (unsigned char)(((1 - (2 * (1 - x) * (1 -y))) * SIZEBYTE) + ROUND);
            }
            // Green
            x = ((float)lhs.pixelData[i].green  / SIZEBYTE);
            y = ((float)rhs.pixelData[i].green  / SIZEBYTE);
            if (y < 0.5f) {
                resultPixels[i].green =  (unsigned char)(((2.0f * x * y) * SIZEBYTE) + ROUND);
            }
            else {
                resultPixels[i].green =  (unsigned char)(((1 - (2 * (1 - x) * (1 -y))) * SIZEBYTE) + ROUND);
            }
            // Red
            x = ((float)lhs.pixelData[i].red  / SIZEBYTE);
            y = ((float)rhs.pixelData[i].red  / SIZEBYTE);
            if (y < 0.5f) {
                resultPixels[i].red =  (unsigned char)(((2.0f * x * y) * SIZEBYTE) + ROUND);
            }
            else {
                resultPixels[i].red =  (unsigned char)(((1 - (2 * (1 - x) * (1 -y))) * SIZEBYTE) + ROUND);
            }
        }
        result->pixelData = resultPixels;
    }
    pictures.push_back(result);
}

void ImageProcessingTGA::addAdjustRGB(Picture& pic, unsigned char r, unsigned char g, unsigned char b) {
    Picture* result = new Picture;
    int length = *pic.lengthOfPixelData;
    HeaderTGA* newHeader = new HeaderTGA;
    copyHeader(newHeader, pic.header);
    result->header = newHeader;
    result->lengthOfPixelData = new int(*pic.lengthOfPixelData);

    Pixel* resultPixels = new Pixel[*result->lengthOfPixelData];

    for (int i = 0; i < length; i++) {
        // Blue
        resultPixels[i].blue = clampAddChar(pic.pixelData[i].blue, b);
        // Green
        resultPixels[i].green = clampAddChar(pic.pixelData[i].green, g);
        // Red
        resultPixels[i].red = clampAddChar(pic.pixelData[i].red, r);
    }
    result->pixelData = resultPixels;
    pictures.push_back(result);
}

void ImageProcessingTGA::scaleAdjustRGB(Picture& pic, float r, float g, float b) {
    Picture* result = new Picture;
    int length = *pic.lengthOfPixelData;
    HeaderTGA* newHeader = new HeaderTGA;
    copyHeader(newHeader, pic.header);
    result->header = newHeader;
    result->lengthOfPixelData = new int(*pic.lengthOfPixelData);

    Pixel* resultPixels = new Pixel[*result->lengthOfPixelData];

    for (int i = 0; i < length; i++) {
        // Blue
        resultPixels[i].blue = clampScaleChar(pic.pixelData[i].blue, b);
        // Green
        resultPixels[i].green = clampScaleChar(pic.pixelData[i].green, g);
        // Red
        resultPixels[i].red = clampScaleChar(pic.pixelData[i].red, r);
    }
    result->pixelData = resultPixels;
    pictures.push_back(result);
}

void ImageProcessingTGA::individualChannel(Picture& pic, char channel) {
    Picture* result = new Picture;
    int length = *pic.lengthOfPixelData;
    HeaderTGA* newHeader = new HeaderTGA;
    copyHeader(newHeader, pic.header);
    result->header = newHeader;
    result->lengthOfPixelData = new int(*pic.lengthOfPixelData);
    unsigned char value;

    Pixel* resultPixels = new Pixel[*result->lengthOfPixelData];

    for (int i = 0; i < length; i++) {
        if (channel == 'r') value = pic.pixelData[i].red;
        else if (channel == 'g') value = pic.pixelData[i].green;
        else if (channel == 'b') value = pic.pixelData[i].blue;

        // Blue
        resultPixels[i].blue = value;
        // Green
        resultPixels[i].green = value;
        // Red
        resultPixels[i].red = value;
    }
    result->pixelData = resultPixels;
    pictures.push_back(result);
}

void ImageProcessingTGA::combinePicsEachOneChannel(Picture& red, Picture& green, Picture& blue) {
    Picture* result = new Picture;
    int length = *red.lengthOfPixelData;
    HeaderTGA* newHeader = new HeaderTGA;
    copyHeader(newHeader, red.header);
    result->header = newHeader;
    result->lengthOfPixelData = new int(*red.lengthOfPixelData);

    Pixel* resultPixels = new Pixel[*result->lengthOfPixelData];

    for (int i = 0; i < length; i++) {
        // Blue
        resultPixels[i].blue = blue.pixelData[i].blue;
        // Green
        resultPixels[i].green = green.pixelData[i].green;
        // Red
        resultPixels[i].red = red.pixelData[i].red;
    }
    result->pixelData = resultPixels;
    pictures.push_back(result);
}

void ImageProcessingTGA::rotate180(Picture& pic) {
    Picture* result = new Picture;
    int length = *pic.lengthOfPixelData;
    HeaderTGA* newHeader = new HeaderTGA;
    copyHeader(newHeader, pic.header);
    result->header = newHeader;
    result->lengthOfPixelData = new int(*pic.lengthOfPixelData);

    Pixel* resultPixels = new Pixel[*result->lengthOfPixelData];

    for (int i = 0; i < length; i++) {
        // Blue
        resultPixels[i].blue = pic.pixelData[length -1 - i].blue;
        // Green
        resultPixels[i].green = pic.pixelData[length -1 - i].green;
        // Red
        resultPixels[i].red = pic.pixelData[length -1 - i].red;
    }
    result->pixelData = resultPixels;
    pictures.push_back(result);
}

void ImageProcessingTGA::extraCreditCombine4Pics(Picture& topLeft, Picture& topRight, Picture& bottomLeft, Picture& bottomRight) {
    Picture* result = new Picture;
    int lengthInitial = *topLeft.lengthOfPixelData;
    int* lengthFinal = new int(lengthInitial * 4);
    int halfWay = *lengthFinal / 2;
    int width = topLeft.header->width;
    HeaderTGA* newHeader = new HeaderTGA;
    copyHeader(newHeader, topLeft.header);
    result->header = newHeader;
    result->header->width = width * 2;
    result->header->height = topLeft.header->height * 2;
    result->lengthOfPixelData = lengthFinal;
    Pixel* resultPixels = new Pixel[*lengthFinal];

    int counterTL = 0;
    int counterTR = 0;
    int counterBL = 0;
    int counterBR = 0;
    int pictureSelect = 0;

    for (int i = 0; i < *lengthFinal; i++) {
        pictureSelect = i / width;
        if (i < halfWay ) {
            if (pictureSelect % 2 == 0) {
                // Blue
                resultPixels[i].blue = bottomLeft.pixelData[counterBL].blue;
                // Green
                resultPixels[i].green = bottomLeft.pixelData[counterBL].green;
                // Red
                resultPixels[i].red = bottomLeft.pixelData[counterBL].red;
                counterBL++;
            }
            else {
                // Blue
                resultPixels[i].blue = bottomRight.pixelData[counterBR].blue;
                // Green
                resultPixels[i].green = bottomRight.pixelData[counterBR].green;
                // Red
                resultPixels[i].red = bottomRight.pixelData[counterBR].red;
                counterBR++;
            }
        }
        else {
            if (pictureSelect % 2 == 0) {
                // Blue
                resultPixels[i].blue = topLeft.pixelData[counterTL].blue;
                // Green
                resultPixels[i].green = topLeft.pixelData[counterTL].green;
                // Red
                resultPixels[i].red = topLeft.pixelData[counterTL].red;
                counterTL++;
            }
            else {
                // Blue
                resultPixels[i].blue = topRight.pixelData[counterTR].blue;
                // Green
                resultPixels[i].green = topRight.pixelData[counterTR].green;
                // Red
                resultPixels[i].red = topRight.pixelData[counterTR].red;
                counterTR++;
            }
        }
    }
    result->pixelData = resultPixels;
    pictures.push_back(result);
}

/**************************************************************
 * ************************ Test Code *************************
 * ************************************************************/

// This functions test equivalence between 2 pictures 1 byte at a time. 
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
        //cout << "Files size. LHS size: " << lengthLhs << " RHS: " << lengthRhs << endl;

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
            return 0;
        }
    }
    else {
        cout << "Files did not open properly. Check filename and location." << endl;
        return 0;
    }
    // Return 1 for success
    cout << "Test Passsed, files are the same." << endl;
    fileInput.close();
    fileRhs.close();
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

/**************************************************************
 * ********************** Helper Functions ********************
 * ************************************************************/

unsigned char ImageProcessingTGA::clampSubtractChar(unsigned char& lhs, unsigned char& rhs) {
    if ((lhs - rhs) < 0) return (char)0;
    else return (lhs - rhs);
}

unsigned char ImageProcessingTGA::clampAddChar(unsigned char& lhs, unsigned char& rhs) {
    if ((lhs + rhs) > 255) return (char)255;
    else return (lhs + rhs);
}

unsigned char ImageProcessingTGA::clampScaleChar(unsigned char& color, float& scale) {
    if ((color * scale) > 255) return (char)255;
    else if ((color * scale) < 0) return (char)0;
    else return (char)((color * scale) + 0.5f);
}

void ImageProcessingTGA::copyHeader(HeaderTGA* dest, HeaderTGA* src) {
    dest->idLength = src->idLength;
    dest->colorMapType = src->colorMapType;
    dest->dataTypeCode = src->dataTypeCode;
    dest->colorMapOrigin = src->colorMapOrigin;
    dest->colorMapLength = src->colorMapLength;
    dest->colorMapDepth = src->colorMapDepth;
    dest->xOrigin = src->xOrigin;
    dest->yOrigin = src->yOrigin;
    dest->width = src->width;
    dest->height = src->height;
    dest->bitsPerPixel = src->bitsPerPixel;
    dest->imageDescriptor = src->imageDescriptor;
}