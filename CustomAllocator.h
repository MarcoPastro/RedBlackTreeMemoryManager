#include <iostream>
#include <list>
#include <cstddef>

struct FreeBlock {
    char* address;
    size_t size;
};


class CustomAllocator {
public:
    CustomAllocator(size_t totalSize);

    ~CustomAllocator();

    void* allocate(size_t size);

    void deallocate(void* ptr);
private:
    char* memoryBlock_;
    std::list<FreeBlock> freeList_;

    void mergeAdjacentBlocks(std::list<FreeBlock>::iterator& it);
};