#include "MemoryManager.h"
#include "stdio.h"

////////////////////////////////////////////////////////////////////////////////////////////////
//                               Main Test 
////////////////////////////////////////////////////////////////////////////////////////////////

void printList(void* list) {
    unsigned short* shList = (unsigned short*)list;
    unsigned short size = shList[0];
    size_t* byteList = (size_t*)list;
    unsigned int length = sizeof(short) + (4 * size * sizeof(char));
    for (unsigned int i = 0; i < length; i++) {
        printf("%X", byteList[i] & 0x000f);
    }
    printf("\n");
}

int main(void) {
    unsigned int wordSize = 2;
    MemoryManager test(wordSize, bestFit);
    test.initialize(100);
    void* getTestList;

    void* firstAlloc20 = test.allocate(20);
    getTestList = test.getList();
    printList(getTestList);
    
    void* secAlloc20 = test.allocate(20);
    getTestList = test.getList();
    printList(getTestList);

    test.free(firstAlloc20);
    getTestList = test.getList();
    printList(getTestList);


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