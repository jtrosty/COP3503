#include "MemoryManager.h"
#include "stdio.h"

////////////////////////////////////////////////////////////////////////////////////////////////
//                               Main Test 
////////////////////////////////////////////////////////////////////////////////////////////////

void printList(void* list) {
    unsigned short* shList = (unsigned short*)list;
    unsigned short size = shList[0];
    size_t* byteList = (size_t*)list;
    unsigned int lengthByte = sizeof(short) + (4 * size * sizeof(char));
    unsigned int lengthShort = (2 * size) + 1;
    for (unsigned int i = 0; i < lengthShort; i++) {
        printf("%s", shList[i]);
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