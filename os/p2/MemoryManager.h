#include <functional>
#include <stdint.h>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <unordered_map>
#include <bitset>
//#include <sys/mman.h>

int worstFit(int sizeInWords, void* list); 
int bestFit(int sizeInWords, void* list); 

class MemoryManager {
    public:
        struct Hole {
            // the start is relative to the address at blockOfMemory.  The start is the byte offset.

            size_t relativeStartInBytes; // In bytes
            size_t sizeInBytes;
            Hole() : relativeStartInBytes(-1), sizeInBytes(-1) {}
            Hole(size_t _start, size_t _size) : relativeStartInBytes(_start), sizeInBytes(_size) {}
        };
    private:
        const unsigned MAX_WORDS = 65536;
        unsigned wordSize;
        void* blockOfMemory;
        unsigned char* bitMap;
        unsigned int numOfBytes; // Total number of bytes initialized. 
        std::vector<Hole> holeTracker;
        std::function<int(int, void*)> currentAllocator;
        std::unordered_map< void*, size_t> allocatedTracker;
        static bool sortHoleByOffset(Hole i, Hole j) { return (i.relativeStartInBytes < j.relativeStartInBytes); }
        static bool sortHoleByLargest(Hole i, Hole j) { return (i.sizeInBytes < j.sizeInBytes); }
        static bool sortHoleBySmallets(Hole i, Hole j) { return (i.sizeInBytes > j.sizeInBytes); }
        void holeAdjustAllocate(int wordOffset, unsigned int byteOffset, unsigned int sizeInBytes);
        void holeAdjustFree(void* address);
    
    public:
        unsigned short* listPtr;
        MemoryManager(unsigned wordSize, std::function<int(int, void*)> allocator);//
        ~MemoryManager();
        void initialize(size_t sizeInWords);//
        void shutdown();
        void* allocate(size_t sizeInBytes);//
        void free(void* address);
        void setAllocator(std::function<int(int, void* )> allocator);//
        int dumpMemoryMap(char* filename);
        void* getList();
        void* getListSortedBySize();
        void* getBitmap();
        unsigned getWordSize();
        void* getMemoryStart();
        unsigned getMemoryLimit();

        int bestFit(int sizeInWords, void* list); //
        int worstFit(int sizeInWords, void* list); //
        
};
