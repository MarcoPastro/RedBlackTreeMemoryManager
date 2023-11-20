template <typename T>
class CustomBigAllocator {
public:
    using value_type = T;

    CustomBigAllocator() = default;

    template <typename U>
    CustomBigAllocator(const CustomBigAllocator<U>& other) {
        (void)other;
    }

    T* allocate(size_t n) {
        T* ptr = static_cast<T*>(malloc(sizeof(T) * n));
        if (ptr)
            return ptr;

        throw std::bad_alloc();
    }

    void deallocate(T* ptr, size_t n) {
        (void)n;
        free(ptr);
    }
};