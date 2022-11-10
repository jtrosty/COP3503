#include <stdlib.h>

unsigned char *testLSFR(unsigned char *data, int dataLength, unsigned int initialValue);
unsigned char *LSFR(unsigned char *data, int dataLength, unsigned int initialValue); 
void shiftRight(unsigned char *data, int dataLength); 
void XORarray(unsigned char *data, int dataLength);

int main(void) {
    unsigned char *data;
    int size = 5;
    data = (unsigned char*)malloc(size);
    data[0] = 'a';
    data[1] = 'p';
    data[2] = 'p';
    data[3] = 'l';
    data[4] = 'e';
    unsigned int feedback = 0x87654321;
    unsigned int initial = 0x12345678;
    //testLSFR(data, size, feedback);
    //testLSFR(data, size, initial);
    LSFR(data, size, initial);
    LSFR(data, size, initial);


    return 0;
}

unsigned char *LSFR(unsigned char *data, int dataLength, unsigned int initialValue) {
    unsigned int feedback = 0x87654321;
    char lowestBit = 0x00;
    int bitsInByte = 8;

    for (int j = 0; j < dataLength; j++) {
        char keyByte = 0;
        for (int i = 0; i < bitsInByte; i++) {
            lowestBit = initialValue & 0x00000001;
            initialValue = initialValue >> 1;
            if (lowestBit == 1)  {
                initialValue = initialValue ^ feedback;
            }
            keyByte = initialValue & 0x000000FF;
        }
        //data[dataLength - j - 1] = data[dataLength - j - 1] ^ keyByte;
        data[j] = data[j] ^ keyByte;
    }
    return data;
}

void shiftRight(unsigned char *data, int dataLength)  {
    unsigned char current = 0x00;
    unsigned char previous = 0x00;
    // Shift
    for (int i = 0; i < dataLength; i++) {
        previous = current;
        current = (data[i] & 0x01) << 7;

        data[i] = data[i] >> 1;
        // Take the previous elements LSB that was shifted out and transfer to the next element in array. 
        if (i == 0) {
            // Skip first element 
        }
        else {
            data[i] = data[i] | previous;
        }
    }
}

void XORarray(unsigned char *data, int dataLength, unsigned int feedback)  { 
    int *dataInt = (int*)data;
    *dataInt = (*dataInt) ^ feedback;
}

unsigned char *testLSFR(unsigned char *data, int dataLength, unsigned int initialValue) {
    unsigned int feedback = 0x87654321;
    char lowestBit = 0x00;
    char lowestBitInitial = 0x00;

    for (int i = 0; i < 8; i++) {
        lowestBitInitial = initialValue & 0x00000001;
        initialValue = initialValue >> 1;
        if (lowestBitInitial == 1)  {
            initialValue = initialValue ^ feedback;
        }
    }

    for (int i = 0; i < 8; i++) {
        lowestBit = data[dataLength - 1] & 0x01;
        shiftRight(data, dataLength);
        if (lowestBit == 1)  {
            XORarray(data, dataLength, feedback);
        }
    }

    return data;
}
