
#include <iostream>
#include <memory>
#include <mutex>
#include <list>
#include <tuple>
#include <map>
#include <thread>
#include <vector>
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

// Define types
using Key = int; // Example key type
using A = double; // Example type A
using B = float; // Example type B
using C = char; // Example type C

// Define custom allocators for A and B
using AlignedAllocatorA = AlignedAllocator<A>;
using AlignedAllocatorB = AlignedAllocator<B>;

// Define a tuple with custom allocators for A and B, and default allocator for C
using MyTuple = std::tuple<
    std::allocator_traits<AlignedAllocatorA>::value_type, // A (uses AlignedAllocatorA)
    std::allocator_traits<AlignedAllocatorB>::value_type, // B (uses AlignedAllocatorB)
    C  // Uses default allocator
>;

// Define a list with the default allocator
using MyList = std::list<MyTuple>;

// Define the map with default allocator for Key and C, and custom allocators for A and B
std::map<Key, MyList> mp;

// Test function to insert data into the map
void insertData(int key, const MyTuple& value) {
    mp[key].push_back(value);
}

// Test function to print the map
void printMap() {
    for (const auto& [key, list] : mp) {
        std::cout << "Key: " << key << "\n";
        for (const auto& tuple : list) {
            std::cout << "  Tuple: (" << std::get<0>(tuple) << ", "
                      << std::get<1>(tuple) << ", "
                      << std::get<2>(tuple) << ")\n";
        }
    }
}

int main() {
    // Test case 1: Insert data into the map
    MyTuple tuple1 = std::make_tuple(1.5, 2.3f, 'a');
    MyTuple tuple2 = std::make_tuple(3.7, 4.1f, 'b');
    MyTuple tuple3 = std::make_tuple(5.9, 6.8f, 'c');

    insertData(1, tuple1);
    insertData(2, tuple2);
    insertData(1, tuple3);

    // Test case 2: Print the map
    std::cout << "Map contents:\n";
    printMap();

    // Test case 3: Multithreaded insertion
    std::vector<std::thread> threads;
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back([i]() {
            MyTuple tuple = std::make_tuple(static_cast<A>(i), static_cast<B>(i), static_cast<C>('a' + i));
            insertData(i % 3, tuple);
        });
    }

    for (auto& t : threads) {
        t.join();
    }

    // Test case 4: Print the map after multithreaded insertion
    std::cout << "\nMap contents after multithreaded insertion:\n";
    printMap();

    return 0;
}
