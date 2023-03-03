#include <stdio.h>
#include <stdint.h>

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
        rawInstructionsData = malloc(sizeof(char) * fileSize);
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
        rawInstructionsData[i] = (char*)(c | 0x000000FF);
    }

    return 0;
}