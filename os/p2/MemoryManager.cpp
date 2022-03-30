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
    if (blockOfMemory != nullptr) MemoryManager::shutdown();
    if (sizeInWords > 65536) sizeInWords = 65536;

    numOfBytes = sizeInWords * wordSize;

    blockOfMemory = calloc(1, numOfBytes);
    if (blockOfMemory == NULL) printf("Failed to allocated memory");
    listPtr = nullptr;
    bitMap = nullptr;
    short* address =  (short*)blockOfMemory;

/*
    for (int i = 0; i < numOfBytes; i++) {
        *address = 0;
        address++;
    }
    //Hole* testHole = new Hole(0, numOfBytes);
    */

    // Worry about mmap later and munmap Hole(0, numOfBytes)
    holeTracker.push_back(Hole(0, numOfBytes));
}

////////////////////////////////////////////////////////////////////////////////////////////////
//                               Destructor and Shutdown 
////////////////////////////////////////////////////////////////////////////////////////////////
MemoryManager::~MemoryManager() {
    if (listPtr != nullptr) delete[] listPtr;
    if (bitMap != nullptr) delete[] bitMap;
    std::free(blockOfMemory);
}

void MemoryManager::shutdown() {
    if (blockOfMemory != nullptr) {
        std::free(blockOfMemory);
        blockOfMemory = nullptr;
        if (listPtr != nullptr) delete[] listPtr;
        if (bitMap != nullptr) delete[] bitMap;
        listPtr = nullptr;
        bitMap = nullptr;
        holeTracker.clear();
        allocatedTracker.clear();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////
//                               Allocator and Hole Adjust Functions
////////////////////////////////////////////////////////////////////////////////////////////////

void MemoryManager::setAllocator(std::function<int(int, void* )> allocator) {
    currentAllocator = allocator;
}

void MemoryManager::holeAdjustAllocate(int wordOffset, unsigned int byteOffset, unsigned int sizeInBytes) {
    // Linear time, maybe a better way to orgainize with a tree? A set would probably be best
    int holeToAdjust = -1;
    for (int i = 0; i < holeTracker.size(); i++) {
        if (holeTracker.at(i).relativeStartInBytes == byteOffset) {
            holeToAdjust = i;
            break;
        }
    }
    if (holeToAdjust != -1) {
        holeTracker.at(holeToAdjust).relativeStartInBytes += sizeInBytes;
        holeTracker.at(holeToAdjust).sizeInBytes -= sizeInBytes;
        if (holeTracker.at(holeToAdjust).sizeInBytes == 0) {
            // Delete the hole
            holeTracker.erase(holeTracker.begin() + holeToAdjust);
       }
    }
}

void* MemoryManager::allocate(size_t sizeInBytes) {
    int needToKnow = sizeof(size_t);
    int sizeUINT64 = sizeof(uint64_t);
    void* sortedByHoleSize = getListSortedBySize();
    int sizeInWords = sizeInBytes / wordSize;
    if (sortedByHoleSize == NULL) return nullptr;
    int wordOffset = currentAllocator(sizeInWords, sortedByHoleSize);
    if (wordOffset == -1)  {
        printf("Unable to allocated enough memory.");
        // Compaction? 
    }
    else {
        unsigned byteOffset = wordOffset * wordSize;
        void* result = (void*)((int*)blockOfMemory + byteOffset);
        holeAdjustAllocate(wordOffset, byteOffset, sizeInBytes);
        // code to allocated
        allocatedTracker.emplace(result, sizeInBytes);
        return result;
    }
}

void MemoryManager::free(void* address) {
    // Get the offset
    size_t offset = (size_t)address - (size_t)blockOfMemory;
    int sizeAll = allocatedTracker.size(); // TODO REMOVE

    size_t sizeInBytes = allocatedTracker.at(address);
    allocatedTracker.erase(address);
    int holeToAdjust = -1;

    // Create hole
    holeTracker.push_back(Hole(offset, sizeInBytes));

    // Sort
    std::sort (holeTracker.begin(), holeTracker.end(), sortHoleByOffset);

    // Find the hole I just added and sorted
    for (int i = 0; i < holeTracker.size(); i++) {
        if (holeTracker.at(i).relativeStartInBytes == offset) {
            holeToAdjust = i;
            break;
        }
    }

    char mergeBack = 0;
    // TODO: Remove
    int size = holeTracker.size();

    if (holeToAdjust > 0) {
        auto prevHole = holeTracker.at(holeToAdjust - 1);
        if ((prevHole.relativeStartInBytes + prevHole.sizeInBytes) == offset) {
            holeTracker.at(holeToAdjust - 1).sizeInBytes += sizeInBytes;
            mergeBack = 1;
        }
    }
    if (holeToAdjust < holeTracker.size() - 1) {
        auto nextHole = holeTracker.at(holeToAdjust + 1);
        if (nextHole.relativeStartInBytes == offset + sizeInBytes) {
            if (mergeBack == 1) {
                holeTracker.at(holeToAdjust - 1).sizeInBytes += holeTracker.at(holeToAdjust + 1).sizeInBytes;
                holeTracker.erase(holeTracker.begin() + holeToAdjust); // The 'next hole' will now be where the hole to adjust was
                holeTracker.erase(holeTracker.begin() + holeToAdjust); // The 'next hole' will now be where the hole to adjust was
            }
            else {
                holeTracker.at(holeToAdjust + 1).sizeInBytes += sizeInBytes;
                holeTracker.at(holeToAdjust + 1).relativeStartInBytes = offset;
                holeTracker.erase(holeTracker.begin() + holeToAdjust);
            }
        }
        else if (mergeBack == 1) {
            holeTracker.erase(holeTracker.begin() + holeToAdjust); // The 'next hole' will now be where the hole to adjust was
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
    // math to support

    int numOfBitsInByte = 8;
    int numOfBytesForSizeOfBitmap = 2; // The number of bytes at the begining of the bitmap that say the number of bytes in the bitmap.
    int numOfBitsInBitMap = numOfBytes / wordSize; 
    int numOfBytesInBitMap = numOfBitsInBitMap / 8;
    if (numOfBitsInBitMap % 8 != 0) numOfBytesInBitMap++; // If not divisible by 8, add another byte.
    int roundToEight = numOfBytesInBitMap * 8;

    // This is the minimum nuimber of bytes needed to represent each word as a bit. 
    int totalNumBytesForBitMap = numOfBytesForSizeOfBitmap + numOfBytesInBitMap;
    int totalNumOfBits = totalNumBytesForBitMap * 8;

    std::sort (holeTracker.begin(), holeTracker.end(), sortHoleByOffset);
    auto iter = holeTracker.begin();
    bitMap = new unsigned char[totalNumBytesForBitMap];
    std::vector<bool> vectorBitMap;

    ((unsigned short*)bitMap)[0] = numOfBytesInBitMap;
    for (int i = 2; i < totalNumBytesForBitMap; i++) {
        bitMap[i] = 0; // Load everythign as 1.
    }
    unsigned char byteToInsert = 0x00;
    for (int i = 0, j = 1; i < roundToEight; i++, j++) {
        size_t currRelStartInWords = iter->relativeStartInBytes / wordSize;
        size_t currSizeInWords = iter->sizeInBytes / wordSize;
        if (i >= numOfBitsInBitMap) byteToInsert = byteToInsert << 1;
        else if (iter == holeTracker.end() || i < currRelStartInWords || i == (currRelStartInWords + currSizeInWords)) {
            //byteToInsert = (byteToInsert >> 1) | 0x80; // should set it to 1
            byteToInsert = (byteToInsert << 1) | 0x01; // should set it to 1
            if (i == (currRelStartInWords + currSizeInWords)) iter++;
        }
        else if (i >= currRelStartInWords && i < (currRelStartInWords + currSizeInWords)) {
            //byteToInsert = byteToInsert >> 1;  // pushes a zero onto the bitpmap
            byteToInsert = byteToInsert << 1;  // pushes a zero onto the bitpmap
        }
        if (j % 8 == 0) {
            //bitMap[(i / 8) + 2] = byteToInsert;
            // flip a bit
            unsigned char bit1 = ((byteToInsert & 0b10000000) >> 7);
            unsigned char bit2 = ((byteToInsert & 0b01000000) >> 5);
            unsigned char bit3 = ((byteToInsert & 0b00100000) >> 3);
            unsigned char bit4 = ((byteToInsert & 0b00010000) >> 1);
            unsigned char bit5 = ((byteToInsert & 0b00001000) << 1);
            unsigned char bit6 = ((byteToInsert & 0b00000100) << 3);
            unsigned char bit7 = ((byteToInsert & 0b00000010) << 5);
            unsigned char bit8 = ((byteToInsert & 0b00000001) << 7);
            byteToInsert = bit1 | bit2 | bit3 | bit4 | bit5 | bit6 | bit7 | bit8;

            bitMap[(i / 8) + 2] = byteToInsert;
            /*
            if (byteToInsert == 0xFF || byteToInsert == 0x00) 
                bitMap[(i / 8) + 2] = byteToInsert;
            else 
                bitMap[(i / 8) + 2] = byteToInsert ^ 0xFF;
            */
            //bitMap[totalNumBytesForBitMap - (i / 8) - 1] = byteToInsert;
            byteToInsert = 0;
            j = 0;
        }
    }
    /*
    int testNum = ((short*)bitMap)[0];
    for (int k = 0; k < testNum; k++) {
        printf("%i", bitMap[k]);
    }
    printf("\n");
    */
    return bitMap;

    //vectorBitMap.resize(totalNumOfBits);


    // Creates the first to bytes, the number of bytes in the rest of the bitMap
    /*
    for (int i = 0; i < 16; i++) {
        vectorBitMap.push_back(numOfBytesInBitMap % 2);
        numOfBytesInBitMap = numOfBytesInBitMap / 2;
    }
    for (int i = 16; i < numOfBitsInBitMap; i++) {
        size_t currRelStartInWords = iter->relativeStartInBytes / wordSize;
        size_t currSizeInWords = iter->sizeInBytes / wordSize;
        if(i < currRelStartInWords || iter == holeTracker.end()) {
            vectorBitMap.at(i) = 1;
        }
        else if (i >= currRelStartInWords && i < (currRelStartInWords + currSizeInWords)) {
            vectorBitMap.at(i) = 0;
        }
        else if(i == (currRelStartInWords + currSizeInWords)) {
            vectorBitMap.at(i) = 1;
            iter++;
        }
    }
    */

    /*
    // No initial size
    for (int i = 16; i < numOfBitsInBitMap; i++) {
        size_t currRelStartInWords = iter->relativeStartInBytes / wordSize;
        size_t currSizeInWords = iter->sizeInBytes / wordSize;
        if(i < currRelStartInWords || iter == holeTracker.end()) {
            vectorBitMap.push_back(1);
        }
        else if (i >= currRelStartInWords && i < (currRelStartInWords + currSizeInWords)) {
            vectorBitMap.push_back(0);
        }
        else if(i == (currRelStartInWords + currSizeInWords)) {
            vectorBitMap.push_back(1);
            iter++;
        }
    }
    for (int i = 0; i < 16; i++) {
        vectorBitMap.push_back(numOfBytesInBitMap % 2);
        numOfBytesInBitMap = numOfBytesInBitMap / 2;
    }

    */
}

void* MemoryManager::getList() {
    size_t size = holeTracker.size();
    size_t listSize = 1 + (size * 2);
    std::sort (holeTracker.begin(), holeTracker.end(), sortHoleByOffset);

    if (size == 0) return NULL;
    if (listPtr != nullptr) {
        delete[] listPtr;
        listPtr = nullptr;
    }
    listPtr = new unsigned short[listSize];

    listPtr[0] = size;
    for (int i = 0, j = 1; i < size; i++, j +=2) {
        listPtr[j] = (holeTracker.at(i).relativeStartInBytes) / wordSize;
        listPtr[j + 1] = (holeTracker.at(i).sizeInBytes) / wordSize;
    }
    return listPtr;
}

void* MemoryManager::getListSortedBySize() {
    size_t size = holeTracker.size();
    size_t listSize = 1 + (size * 2);
    std::sort (holeTracker.begin(), holeTracker.end(), sortHoleByLargest);

    if (size == 0) return NULL;
    if (listPtr != nullptr) {
        delete[] listPtr;
        listPtr = nullptr;
    }
    listPtr = new unsigned short[listSize];

    listPtr[0] = size;
    for (int i = 0, j = 1; i < size; i++, j +=2) {
        listPtr[j] = (holeTracker.at(i).relativeStartInBytes) / wordSize;
        listPtr[j + 1] = (holeTracker.at(i).sizeInBytes) / wordSize;
    }
    return listPtr;
}

unsigned MemoryManager::getWordSize() {
    return wordSize;
}

void* MemoryManager::getMemoryStart() {
    return blockOfMemory;
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
    unsigned short* shList = (unsigned short*)list;
    unsigned short size = shList[0];
    for (int i = 1; i <= size; i += 2) {
        // This assumes that it is sorted from smallet to largest
        int shListWordSize = shList[i + 1];
        if (sizeInWords < shList[i + 1] || sizeInWords == shList[i + 1]) {
            bestFit = i;
            break;
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
    return result;
}

// Worst Fit
// TODO: make sure this is f'd 
int worstFit(int sizeInWords, void* list) {
    int worstFit = -1;
    unsigned short* shList = (unsigned short*)list;
    unsigned short size = shList[0];
    //We just need the biggest space available. 
    int result = -2;
    int value2 = shList[(2*size)];
    int value = shList[(2*size) - 1];
    if ((size > 0) && (shList[(2 * size)] >= sizeInWords)) {
        result = shList[(2 * size) - 1];
    }
    else {
        result = -1;
    }
    return result;
}
