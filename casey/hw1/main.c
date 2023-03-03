#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

long getfileSize(char* filename) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("File faailed to open.");
    }
    if (fseek(fp, 0, SEEK_END) < 0) {
        fclose(fp);
        perror("File faailed to open.");
    }
    long length = ftell(fp);
    fclose(fp);
    return length;
}


void decode(uint16_t fullInst) {
    const uint8_t const movRtoR = 0x00100010;

    printf("%X \n", fullInst);
    uint8_t opcode = (fullInst > 10) ; // need the first 6 bits
    switch (opcode) {
        case 0x00100010: {
            mov(fullInst);
            break;
        } 
    }
}

void mov(uint16_t fullInst) {
    printf("mov ");
}

int main(int argc, char* argv[]) {
    FILE* fp;
    char* rawInstructionsData;
    char* debug_fileName;
    long fileSize = 0;


    if (argc == 2) {
        fileSize = getfileSize(argv[1]);
        if (fileSize == 0) {
            perror("File filed to open.");
        }
    }
    else if (argc == 1) {
        debug_fileName = "short_test.bin";
        fileSize = getfileSize(debug_fileName);
        if (fileSize == 0) {
            perror("File filed to open.");
        }
        size_t bytes = sizeof(char) * ((int)fileSize);
        //rawInstructionsData = (char*)malloc(bytes);
        rawInstructionsData = (char*)malloc(bytes * sizeof(char));
        if (!rawInstructionsData) {
            perror("Failed to get memory.");
        }
        fp = fopen(debug_fileName, "r");
    }
    else {
        return 1;
    }
    // It worked. 

    // Copy raw data into new array to be passed to encoding.
    int c;
    for (long i = 0; i < fileSize; i++) {
        c = fgetc(fp);
        if (feof(fp)) {
            break;
        }
        char temp = (char)(c & 0x000000FF);
        rawInstructionsData[i] = temp;
    }
    fclose(fp);

    if (fileSize % 2 ==1) {
        perror("odd number of bytes in instructions.");
    }

    long numOfInstructiosn = fileSize / 2;
    uint16_t* inst = (uint16_t*)rawInstructionsData;
    for (long i = 0; i < numOfInstructiosn; i++) {
        decode(inst[i]);
    }


    free(rawInstructionsData);
    printf("you did it. \n");
    return 0;
}