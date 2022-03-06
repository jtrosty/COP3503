#include "MemoryManager.h"

////////////////////////////////////////////////////////////////////////////////////////////////
//                               Constructor and Destructor 
////////////////////////////////////////////////////////////////////////////////////////////////

MemoryManager::MemoryManager(unsigned wordSize, std::function<int(int, void*)> allocator) {
    numOfBytes = 0;
    wordSize = wordSize;
    blockOfMemory = nullptr;
    currentAllocator = allocator;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//                               Core Functionality 
////////////////////////////////////////////////////////////////////////////////////////////////

void MemoryManager::initialize(size_t sizeInWords) {
    // TODO Do I need to free all memory allocated?
    // Or do I have to copy memory from previous region to newly initialized region.
    numOfBytes = sizeInWords * wordSize;

    blockOfMemory = malloc(numOfBytes);

    // Worry about mmap later and munmap
    

    hole firstHole;
    firstHole.start = 0;
    firstHole.size = numOfBytes;
    holeTracker.push_back(firstHole);
    
}

////////////////////////////////////////////////////////////////////////////////////////////////
//                               Destructor and Shutdown 
////////////////////////////////////////////////////////////////////////////////////////////////
MemoryManager::~MemoryManager() {
    free(blockOfMemory);
}

void MemoryManager::shutdown() {
    free(blockOfMemory);
}

////////////////////////////////////////////////////////////////////////////////////////////////
//                               Allocator Functions
////////////////////////////////////////////////////////////////////////////////////////////////


void* MemoryManager::allocate(size_t sizeInBytes) {
    void* testList = 0;
    int sizeInWords = sizeInBytes / wordSize;
    int wordOffset = currentAllocator(sizeInWords, testList);
    if (wordOffset == -1)  {
        printf("Unable to allocated enough memory.");
        // Compaction? 
    }
    else {
        unsigned byteOffset = wordOffset * wordSize;
        void* result = (int*)blockOfMemory + sizeof(byteOffset);
        return result;
    }
}

// Best Fit
int MemoryManager::bestFit(int sizeInWords, void* list) {
    // need the smallet hole that will fit the memory
    std::sort (holeTracker.begin(), holeTracker.end(), sortHole);
    int bestFit = -1;
    for (int i = 0; i < holeTracker.size(); i++) {
        // This assumes that it is sorted from smallet to largest
        if (sizeInWords < holeTracker.at(i).size) {
            bestFit = i;
        }
        else {
            // hole is not big enough
            break;
        }
    }
    if (bestFit == -1) {
        //no space big enough
        printf("No hole is large enough for memory.");
        return bestFit;
    }
    return holeTracker.at(bestFit).start;
}

// Worst Fit
int MemoryManager::worstFit(int sizeInWords, void* list) {
    // Need the largest hole that fits the required bit
    std::sort (holeTracker.begin(), holeTracker.end(), sortHole);
    int bestFit = -1;
    int lastIndex = holeTracker.size() - 1;
    if (holeTracker.at(lastIndex).size < sizeInWords) {
        bestFit = lastIndex;
    }
    if (bestFit == -1) {
        //no space big enough
        printf("No hole is large enough for memory.");
        return bestFit;
    }
    return holeTracker.at(bestFit).start;
}


////////////////////////////////////////////////////////////////////////////////////////////////
//                               Get Functions
////////////////////////////////////////////////////////////////////////////////////////////////

unsigned MemoryManager::getWordSize() {
    return wordSize;
}

void* MemoryManager::getMemoryStart() {
    return &blockOfMemory;
}

unsigned MemoryManager::getMemoryLimit() {
    return numOfBytes;
}

