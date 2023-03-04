#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

char* regTable[2][8] = {{"AL", "CL", "DL", "BL", "AH", "CH", "DH", "BH"}, 
                        {"AX", "CX", "DX", "BX", "SP", "BP", "SI", "DI"}};

long getfileSize(char* filename) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("File failed to open.");
    }
    if (fseek(fp, 0, SEEK_END) < 0) {
        fclose(fp);
        perror("File failed to open.");
    }
    long length = ftell(fp);
    fclose(fp);
    return length;
}

void printMovInst(char regTo, char regFrom, char w) {
    printf("MOV %s, %s \n", regTable[w][regTo], regTable[w][regFrom]);
}

void movRtoR(uint16_t fullInst) {
    // MOV register to register
    char dir;
    char word;
    char mod;
    char regFrom;
    char regTo;

    // Get direciton of move
    if ((fullInst & 0x0002) > 0) dir = 1;
    else dir = 0;
    // Get if it is a full word or not
    if ((fullInst & 0x0001) > 0) word = 1;
    else word = 0;

    mod = (fullInst & 0xC000) >> 14;
    regFrom = (fullInst & 0x3800) >> 11;
    regTo = (fullInst & 0x0700) >> 8;
    printMovInst(regTo, regFrom, word);
}

void decode(uint16_t fullInst) {

    //TODO: Debug code to remove 
    //printf("%X \n", fullInst);
    //
    uint8_t opcode = (fullInst & 0x00FC); // need the first 6 bits
    switch (opcode) {
        case 0b10001000: {
            movRtoR(fullInst);
            break;
        } 
    }
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
        //debug_fileName = "short_test.bin";
        debug_fileName = "many_test.bin";

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