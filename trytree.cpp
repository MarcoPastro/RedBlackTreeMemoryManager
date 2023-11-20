#include "CustomAllocatorRBTree.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <list>
int main() {
    const size_t totalSize = 1024;
    CustomAllocatorRBTree* allocator = new CustomAllocatorRBTree(totalSize);

    // Allocate memory blocks using your custom allocator
    void* block1 = allocator->Allocate(128);
    void* block2 = allocator->Allocate(256);
    void* block3 = allocator->Allocate(64);

    std::cout << "allocated" << std::endl;
    // Deallocate memory blocks when done
    allocator->Deallocate(block1, 128);
    std::cout << "deallocated block1 128" << std::endl;
    allocator->Deallocate(block2, 256);
    std::cout << "deallocated block2 256" << std::endl;
    allocator->Deallocate(block3, 64);
    std::cout << "deallocated block3 64" << std::endl;

    delete allocator;
    return 0;
}
