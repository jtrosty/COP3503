#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

char* regTable[2][8] = {{"AL", "CL", "DL", "BL", "AH", "CH", "DH", "BH"}, 
                        {"AX", "CX", "DX", "BX", "SP", "BP", "SI", "DI"}};

void setup_debug_handlers(void);
void dump_stack_trace(void);

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
    uint8_t opcodeFourBits = (fullInst & 0x00F0); // need the first 6 bits
    uint8_t nextTwoBits = (fullInst & 0x000C);
    switch (opcodeFourBits) {
        case 0xA0: { // 1000
            // TODO: mem to accumlator, accum to mem 
            break;
        }
        case 0xB0: { // 1000
            // TODO: add immediate register move
            break;
        }
        case 0x80: { // 1000
            switch (nextTwoBits)
            {
                case 0x0080:
                    movRtoR(fullInst);
                    break;
                case 0x00C0:
                    // TODO: 
                    // Add reg/mem to segreg
                    // Add segment rgister/mem
                    break;
                default:
                    break;
            }
        } 
    }
}

int run_8086(int argc, char* argv[]) {
    FILE* fp;
    char* rawInstructionsData;
    char* debug_fileName;
    long fileSize = 0;
    setup_debug_handlers();


    printf("Hello we are in the program.");
    if (argc == 2) {
        fileSize = getfileSize(argv[1]);
        if (fileSize == 0) {
            perror("File filed to open.");
        }
    }
    else if (argc == 1) {
        //debug_fileName = "../short_test.bin";
        debug_fileName = "data/many_test.bin";

        fileSize = getfileSize(debug_fileName);
        if (fileSize == 0) {
            perror("File filed to open.");
        }
        size_t bytes = sizeof(char) * ((int)fileSize);
        //rawInstructionsData = (char*)malloc(bytes);
        rawInstructionsData = (char*)malloc(bytes * sizeof(char));
        rawInstructionsData[50000] = 21312;
        printf("Printing %i", rawInstructionsData[50000]);
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