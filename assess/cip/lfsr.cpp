#include <stdlib.h>

unsigned char *testLSFR(unsigned char *data, int dataLength, unsigned int initialValue);
void shiftRight(unsigned char *data, int dataLength); 
void XORarray(unsigned char *data, int dataLength);

int main(void) {
    unsigned char *data;
    int size = 4;
    data = (unsigned char*)malloc(size);
    for (int i = 0; i < size; i++) {
        data[i] = 0xFF;
    } 
    unsigned int feedback = 0x87654321;
    unsigned int initial = 0xFFFFFFFF;
    testLSFR(data, size, feedback);
    testLSFR(data, size, initial);


    return 0;
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
