#include "MemoryManager.h"

////////////////////////////////////////////////////////////////////////////////////////////////
//                               Constructor and Destructor 
////////////////////////////////////////////////////////////////////////////////////////////////

MemoryManager::MemoryManager(unsigned wordSize, std::function<int(int, void*)> allocator) {
    numOfBytes = 0;
    this->wordSize = wordSize;
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
    holeTracker.push_back(hole(0, numOfBytes));
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
//                               Allocator and Hole Adjust Functions
////////////////////////////////////////////////////////////////////////////////////////////////

void MemoryManager::holeAdjustAllocate(unsigned int byteOffset, size_t sizeInBytes) {
    // Linear time, maybe a better way to orgainize with a tree? A set would probably be best
    int holeToAdjust = -1;
    for (int i = 0; i < holeTracker.size(); i++) {
        if (holeTracker.at(i).relativeStart == byteOffset) {
            holeToAdjust = i;
            break;
        }
    }
    if (holeToAdjust != -1) {
        holeTracker.at(holeToAdjust).relativeStart += sizeInBytes;
        holeTracker.at(holeToAdjust).sizeInBytes -= sizeInBytes;
        if (holeTracker.at(holeToAdjust).sizeInBytes == 0) {
            // Delete the hole
            holeTracker.erase(holeTracker.begin() + holeToAdjust);
       }
    }
}

void* MemoryManager::allocate(size_t sizeInBytes) {
    void* testList = getList();
    int sizeInWords = sizeInBytes / wordSize;
    int wordOffset = currentAllocator(sizeInWords, testList);
    if (wordOffset == -1)  {
        printf("Unable to allocated enough memory.");
        // Compaction? 
    }
    else {
        unsigned byteOffset = wordOffset * wordSize;
        void* result = (char*)blockOfMemory + byteOffset;
        holeAdjustAllocate(byteOffset, sizeInBytes);
        allocatedTracker.emplace(result, sizeInBytes);
        return result;
    }
}

void MemoryManager::free(void* address) {
    // Get the offset
    int offset = (int)address - (int)blockOfMemory;
    size_t sizeInBytes = allocatedTracker.at(address);
    allocatedTracker.erase(address);
    int holeToAdjust = -1;

    // Create hole
    holeTracker.push_back(hole(offset, sizeInBytes));

    // Sort
    std::sort (holeTracker.begin(), holeTracker.end(), sortHole);

    // Find the hole I just added and sorted
    for (int i = 0; i < holeTracker.size(); i++) {
        if (holeTracker.at(i).relativeStart == offset) {
            holeToAdjust = i;
            break;
        }
    }

    char mergeBack = 0;
    // TODO: Remove
    int sie = holeTracker.size();

    if (holeToAdjust > 0) {
        auto prevHole = holeTracker.at(holeToAdjust - 1);
        if ((prevHole.relativeStart + prevHole.sizeInBytes) == offset) {
            prevHole.sizeInBytes += sizeInBytes;
        }
        mergeBack = 1;
    }
    if (holeToAdjust < holeTracker.size()) {
        auto nextHole = holeTracker.at(holeToAdjust + 1);
        if (nextHole.relativeStart == offset + sizeInBytes) {
            nextHole.sizeInBytes += sizeInBytes;
            nextHole.relativeStart = offset;
            holeTracker.erase(holeTracker.begin() + holeToAdjust);
            if (mergeBack == 1) {
                holeTracker.at(holeToAdjust - 1).sizeInBytes += nextHole.sizeInBytes;
                holeTracker.erase(holeTracker.begin() + holeToAdjust); // The 'next hole' will now be where the hole to adjust was
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////
//                               File Output Function
////////////////////////////////////////////////////////////////////////////////////////////////
int MemoryManager::dumpMemoryMap(char* filename) {

    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//                               Get Functions
////////////////////////////////////////////////////////////////////////////////////////////////

void* MemoryManager::getBitmap() {
    int size = (numOfBytes / wordSize);
    char* bitMap = new char[size + (2 * sizeof(char))];
    for (int i = (2 * sizeof(char)); i < size; i++) {
        bitMap[i] = 1;
    }
    ((short*)bitMap)[0] = size;

    for (auto iter = holeTracker.begin(); iter != holeTracker.end(); iter++) {
        int i = iter->relativeStart;
        int size = iter->sizeInBytes;
        for (i; i < (i + size); i++) {
            bitMap[i] = 0;
        }
    }
    return (void*)bitMap;
}

void* MemoryManager::getList() {
    size_t size = holeTracker.size();
    size_t listSize = 1 + (size * 2);
    std::sort (holeTracker.begin(), holeTracker.end(), sortHole);

    if (size == 0) return NULL;
    unsigned short* list = new unsigned short[listSize];

    list[0] = size;
    for (int i = 1; i < listSize; i += 2) {
        list[i] = holeTracker.at(i - 1).relativeStart;
        list[i + 1] = holeTracker.at(i - 1).sizeInBytes;
    }
    return list;
}

unsigned MemoryManager::getWordSize() {
    return wordSize;
}

void* MemoryManager::getMemoryStart() {
    return &blockOfMemory;
}

unsigned MemoryManager::getMemoryLimit() {
    return numOfBytes;
}

// *********************************************************************************************
//                         END OF CLASS DEFINITION
// *********************************************************************************************
////////////////////////////////////////////////////////////////////////////////////////////////
//                        Best and Worst Fit Functions
////////////////////////////////////////////////////////////////////////////////////////////////
// Best Fit
int bestFit(int sizeInWords, void* list) {
    // need thesmallet hole that will fit the memory

    int bestFit = -1;
    short* shList = (short*)list;
    short size = *shList & 0xF;
    for (int i = 1; i <= size; i += 2) {
        // This assumes that it is sorted from smallet to largest
        if (sizeInWords < shList[i + 1]) {
            bestFit = i;
        }
        else {
            // hole is not big enough
            // The previous point had the best fitting 
            break;
        }
    }
    if (bestFit == -1) {
        //no space big enough
        printf("No hole is large enough for memory.\n");
        return bestFit;
    }
    int result = shList[bestFit];
    free(shList);
    return result;
}

// Worst Fit
// TODO: make sure this is f'd 
int worstFit(int sizeInWords, void* list) {
    int worstFit = -1;
    short* shList = (short*)list;
    short size = shList[0];
    //We just ened teh biggest space available. 
    int result = -2;
    if (size > 0) {
        result = shList[size - 1];
    }
    else {
        result = -1;
    }
    free(shList);
    return result;
}
