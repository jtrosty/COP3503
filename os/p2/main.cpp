#include "MemoryManager.h"
#include "stdio.h"
#include <iostream>
//#pragma comment(linker, "/STACK: 2000000")
using std::cout;
using std::endl;

////////////////////////////////////////////////////////////////////////////////////////////////
//                               Main Test 
////////////////////////////////////////////////////////////////////////////////////////////////

void printList(void* list) {
    unsigned short* shList = (unsigned short*)list;
    unsigned short size = shList[0];
    //unsigned short var1 = shList[1];
    //unsigned short var2 = shList[2];
    //cout << "index 0: " << size << "index 1: " << var1 << " index 2: " << var2 << endl;
    //printf(" 1: %s, 2 %s, 3: $s \n",size, var1, var2 );
    //size_t* byteList = (size_t*)list;
    //unsigned int lengthByte = sizeof(short) + (4 * size * sizeof(char));
    unsigned int lengthShort = (2 * size) + 1;
    for (unsigned int i = 0; i < lengthShort; i++) {
        printf("%hi ", shList[i]);
    }
    printf("\n");
}
/*
void printList(void* list) {
    unsigned short* shList = (unsigned short*)list;
    unsigned short size = shList[0];
    size_t* byteList = (size_t*)list;
    unsigned int length = sizeof(short) + (4 * size * sizeof(char));
    for (unsigned int i = 0; i < length; i++) {
        printf("%s", byteList[i] << 16);
    }
    printf("\n");
}

*/

int main(void) {
    unsigned int wordSize = 2;
    MemoryManager test(wordSize, bestFit);
    test.initialize(100);
    void* getTestList;

    void* firstAlloc20 = test.allocate(20);
    getTestList = test.getList();
    void* getBitMap = test.getBitmap();

    printList(getTestList);
    void* bitMap = test.getBitmap();
    
    void* secAlloc20 = test.allocate(20);
    getTestList = test.getList();
    printList(getTestList);
    bitMap = test.getBitmap();

    test.free(firstAlloc20);
    getTestList = test.getList();
    printList(getTestList);
    bitMap = test.getBitmap();

/*
    void* testAlloc;
    for (int i = 0; i < 100; i++) {
        testAlloc = test.allocate(20);
        test.free(testAlloc);
        
    }

    for (int i = 0, j = 1; i < numOfBitsInBitMap; i++, j++) {
        size_t currRelStartInWords = iter->relativeStartInBytes / wordSize;
        size_t currSizeInWords = iter->sizeInBytes / wordSize;
        if (iter == holeTracker.end()) {
            byteToInsert = (byteToInsert >> 1) | 1u; // should set it to 1
        }
        else if (i < currRelStartInWords) {
            byteToInsert = (byteToInsert >> 1) | 0x8; // should set it to 1
        }
        else if (i >= currRelStartInWords && i < (currRelStartInWords + currSizeInWords)) {
            byteToInsert = byteToInsert >> 1;  // pushes a zero onto the bitpmap
        }
        else if (i == (currRelStartInWords + currSizeInWords)) {
            iter++;
        }
        if (j % 8 == 0) {
            bitMap[(i / 8) + 2] = byteToInsert;
            byteToInsert = 0;
            j = 1;
            
        }
    }

*/
    /*
    test.allocate(20);
    getTestList = test.getList();
    printList(getTestList);
    test.allocate(20);
    getTestList = test.getList();
    printList(getTestList);
    test.allocate(20);
    getTestList = test.getList();
    printList(getTestList);
    */


    return 0;
}