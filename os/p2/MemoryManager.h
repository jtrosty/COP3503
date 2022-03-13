#include <functional>
#include <stdint.h>
#include <vector>
#include <algorithm>
#include <stdio.h>
//#include <sys/mman.h>

class MemoryManager {
    public:
        struct hole {
            int start;
            int size;
        };
    private:
        const unsigned MAX_WORDS = 65536;
        unsigned wordSize;
        void* blockOfMemory;
        size_t numOfBytes;
        std::vector<hole> holeTracker;
        std::function<int(int, void*)> currentAllocator;
        static bool sortHole(hole i, hole j) { return (i.size < j.size); }

    
    public:
        MemoryManager(unsigned wordSize, std::function<int(int, void*)> allocator);//
        ~MemoryManager();
        void initialize(size_t sizeInWords);//
        void shutdown();
        void* allocate(size_t sizeInBytes);//
        //void free(void* address);
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
