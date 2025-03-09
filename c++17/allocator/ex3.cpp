
#include <iostream>
#include <memory>
#include <mutex>
#include <list>
#include <cstdlib> // for std::aligned_alloc and std::free

// Custom aligned allocator with thread safety
template <typename T, std::size_t Alignment = alignof(T)>
class AlignedAllocator {
public:
    using value_type = T;

    AlignedAllocator() = default;

    template <typename U>
    AlignedAllocator(const AlignedAllocator<U, Alignment>&) noexcept {}

    // Rebind mechanism required by the standard allocator model
    template <typename U>
    struct rebind {
        using other = AlignedAllocator<U, Alignment>;
    };

    T* allocate(std::size_t n) {
        std::lock_guard<std::mutex> lock(mutex_); // Ensure thread safety
        void* ptr = std::aligned_alloc(Alignment, n * sizeof(T));
        if (!ptr) {
            throw std::bad_alloc();
        }
        return static_cast<T*>(ptr);
    }

    void deallocate(T* ptr, std::size_t n) noexcept {
        std::lock_guard<std::mutex> lock(mutex_); // Ensure thread safety
        std::free(ptr);
	(void)n;
    }

private:
    static std::mutex mutex_;
};

template <typename T, std::size_t Alignment>
std::mutex AlignedAllocator<T, Alignment>::mutex_;

template <typename T, std::size_t AlignmentA, typename U, std::size_t AlignmentB>
bool operator==(const AlignedAllocator<T, AlignmentA>&, const AlignedAllocator<U, AlignmentB>&) {
    return AlignmentA == AlignmentB;
}

template <typename T, std::size_t AlignmentA, typename U, std::size_t AlignmentB>
bool operator!=(const AlignedAllocator<T, AlignmentA>&, const AlignedAllocator<U, AlignmentB>&) {
    return AlignmentA != AlignmentB;
}

// Define a list with the aligned allocator
using MyList = std::list<int, AlignedAllocator<int>>;

int main() {
    // Create a list with the aligned allocator
    MyList myList;

    // Insert some elements into the list
    for (int i = 0; i < 10; ++i) {
        myList.push_back(i);
    }

    // Print the list contents
    std::cout << "List contents:\n";
    for (const auto& value : myList) {
        std::cout << value << "\n";
    }

    return 0;
}
