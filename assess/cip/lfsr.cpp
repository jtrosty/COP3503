#include <stdlib.h>

unsigned char *testLSFR(unsigned char *data, int dataLength, unsigned int initialValue);

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


unsigned char *testLSFR(unsigned char *data, int dataLength, unsigned int initialValue) {
    char lowestBit = *data & 0x01;
    for (int i = 0; i < 8; i++) {

    }

    return data;
}
