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
    testLSFR(data, size, feedback);


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
        if (i == 0) {
            
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
    char lowestBit = data[dataLength - 1] & 0x01;
    for (int i = 0; i < 32; i++) {
        shiftRight(data, dataLength);
        XORarray(data, dataLength, feedback);
    }

    return data;
}
