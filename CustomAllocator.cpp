#include "CustomAllocator.h"

CustomAllocator::CustomAllocator(size_t totalSize) {
    memoryBlock_ = new char[totalSize];
    freeList_.push_back({ memoryBlock_, totalSize });
}

CustomAllocator::~CustomAllocator() {
    delete[] memoryBlock_;
}

void* CustomAllocator::allocate(size_t size) {
    for (std::list<FreeBlock>::iterator it = freeList_.begin(); it != freeList_.end(); ++it) {
        if (it->size >= size) {
            // Allocate memory from the current free block.
            char* allocatedBlock = it->address;
            if (it->size > size) {
                // Split the free block if it's larger than needed.
                char* newFreeBlock = it->address + size;
                size_t newFreeSize = it->size - size;
                it = freeList_.erase(it);
                freeList_.insert(std::next(it), { newFreeBlock, newFreeSize });
            }
            else {
                // Remove the block from the free list if it's exact size.
                it = freeList_.erase(it);
            }
            return allocatedBlock;
        }
    }

    return nullptr;  // Not enough memory available.
}

    void CustomAllocator::deallocate(void* ptr) {
        char* blockStart = static_cast<char*>(ptr);

        // Find the size of the block being deallocated.
        std::list<FreeBlock>::iterator it = freeList_.begin();
        while (it != freeList_.end()) {
            if (it->address == blockStart) {
                size_t size = it->size;
                // Insert the block as a new free block.
                freeList_.insert(it, { blockStart, size });
                // Merge adjacent free blocks.
                mergeAdjacentBlocks(it);
                return;
            }
            ++it;
        }
    }


    // Helper function to merge adjacent free blocks.
    void CustomAllocator::mergeAdjacentBlocks(std::list<FreeBlock>::iterator& it) {
        std::list<FreeBlock>::iterator current = it;
        std::list<FreeBlock>::iterator next = std::next(it);

        if (next != freeList_.end() && current->address + current->size == next->address) {
            current->size += next->size;
            freeList_.erase(next);
        }

        if (current != freeList_.begin()) {
            auto prev = std::prev(current);
            if (prev->address + prev->size == current->address) {
                prev->size += current->size;
                freeList_.erase(current);
            }
        }
    }