#include <functional>
#include <stdint.h>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <unordered_map>
//#include <sys/mman.h>

int worstFit(int sizeInWords, void* list); 
int bestFit(int sizeInWords, void* list); 

class MemoryManager {
    public:
        struct hole {
            // the start is relative to the address at blockOfMemory.  The start is the byte offset.

            int relativeStart;
            int sizeInBytes;
            hole() : relativeStart(-1), sizeInBytes(-1) {}
            hole(int _start, int _size) : relativeStart(_start), sizeInBytes(_size) {}
        };
    private:
        const unsigned MAX_WORDS = 65536;
        unsigned wordSize;
        void* blockOfMemory;
        size_t numOfBytes;
        std::vector<hole> holeTracker;
        std::function<int(int, void*)> currentAllocator;
        std::unordered_map<void*, size_t> allocatedTracker;
        static bool sortHole(hole i, hole j) { return (i.sizeInBytes < j.sizeInBytes); }
        void holeAdjustAllocate(unsigned int byteOffset, size_t sizeInBytes);
        void holeAdjustFree(void* address);

    
    public:
        MemoryManager(unsigned wordSize, std::function<int(int, void*)> allocator);//
        ~MemoryManager();
        void initialize(size_t sizeInWords);//
        void shutdown();
        void* allocate(size_t sizeInBytes);//
        void free(void* address);
        void setAllocator(std::function<int(int, void* )> allocator);//
        int dumpMemoryMap(char* filename);
        void* getList();
        void* getBitmap();
        unsigned getWordSize();
        void* getMemoryStart();
        unsigned getMemoryLimit();

        int bestFit(int sizeInWords, void* list); //
        int worstFit(int sizeInWords, void* list); //
        
};
