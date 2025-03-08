
#include <iostream>
#include <memory>
#include <cstddef>
#include <vector>
#include <list>
#include <map>
#include <cstdlib>
#include <mutex>

// Base class for custom allocators
class BaseAllocator {
public:
    virtual ~BaseAllocator() = default;

    // Pure virtual methods for allocation and deallocation
    virtual void* allocate(std::size_t size) = 0;
    virtual void deallocate(void* p, std::size_t size) = 0;
};

// Debug allocator: Extends BaseAllocator and provides debug output
class DebugAllocator : public BaseAllocator {
public:
    // Allocate memory and print debug information
    void* allocate(std::size_t size) override {
        std::cout << "Allocating memory for " << size << " bytes\n";
        void* ptr = std::malloc(size); // Use standard malloc
        if (!ptr) throw std::bad_alloc(); // Handle allocation failure
        return ptr;
    }

    // Deallocate memory and print debug information
    void deallocate(void* p, std::size_t size) override {
        std::cout << "Deallocating memory for " << size << " bytes\n";
        std::free(p); // Use standard free
    }
};

// Thread-safe allocator: Extends BaseAllocator and uses a mutex for thread safety
class ThreadSafeAllocator : public BaseAllocator {
public:
    // Allocate memory in a thread-safe manner
    void* allocate(std::size_t size) override {
        std::lock_guard<std::mutex> lock(mutex_); // Lock the mutex
        void* ptr = std::malloc(size); // Use standard malloc
        if (!ptr) throw std::bad_alloc(); // Handle allocation failure
        return ptr;
    }

    // Deallocate memory in a thread-safe manner
    void deallocate(void* p, std::size_t size) override {
        std::lock_guard<std::mutex> lock(mutex_); // Lock the mutex
        std::free(p); // Use standard free
        (void) size;
    }

private:
    std::mutex mutex_; // Mutex for thread safety
};

// Single-threaded allocator: Extends BaseAllocator (no thread safety)
class SingleThreadAllocator : public BaseAllocator {
public:
    // Allocate memory (not thread-safe)
    void* allocate(std::size_t size) override {
        void* ptr = std::malloc(size); // Use standard malloc
        if (!ptr) throw std::bad_alloc(); // Handle allocation failure
        return ptr;
    }

    // Deallocate memory (not thread-safe)
    void deallocate(void* p, std::size_t size) override {
        std::free(p); // Use standard free
        (void) size;
    }
};

// Type-erased allocator: Adapts BaseAllocator to work with STL containers
template <typename T>
class TypeErasedAllocator {
public:
    using value_type = T; // Required by STL containers

    // Constructor: Takes a pointer to a BaseAllocator
    explicit TypeErasedAllocator(BaseAllocator* base_allocator) : base_allocator_(base_allocator) {}

    // Copy constructor: Allows rebinding to other types
    template <typename U>
    TypeErasedAllocator(const TypeErasedAllocator<U>& other) noexcept : base_allocator_(other.base_allocator_) {}

    // Allocate memory for 'n' objects of type T
    T* allocate(std::size_t n) {
        return static_cast<T*>(base_allocator_->allocate(n * sizeof(T)));
    }

    // Deallocate memory for 'n' objects of type T
    void deallocate(T* p, std::size_t n) {
        base_allocator_->deallocate(p, n * sizeof(T));
    }

    // Rebind mechanism: Allows the allocator to be used with other types
    template <typename U>
    struct rebind {
        using other = TypeErasedAllocator<U>;
    };

    // Equality comparison: Required by STL containers
    bool operator==(const TypeErasedAllocator& other) const noexcept {
        return base_allocator_ == other.base_allocator_;
    }

    // Inequality comparison: Required by STL containers
    bool operator!=(const TypeErasedAllocator& other) const noexcept {
        return !(*this == other);
    }

    BaseAllocator* base_allocator_; // Pointer to the base allocator
};

// Buffer FIFO class: A thread-safe FIFO buffer using BaseAllocator
template <typename T>
class BufferFIFO {
public:
    // Constructor: Allocates memory for the buffer
    BufferFIFO(BaseAllocator* allocator, std::size_t capacity)
        : allocator_(allocator), capacity_(capacity), size_(0), head_(0), tail_(0) {
        buffer_ = static_cast<T*>(allocator_->allocate(capacity_ * sizeof(T)));
    }

    // Destructor: Deallocates memory and destroys remaining objects
    ~BufferFIFO() {
        while (size_ > 0) pop(); // Pop all remaining objects
        allocator_->deallocate(buffer_, capacity_ * sizeof(T)); // Deallocate memory
    }

    // Push an element into the buffer
    void push(const T& value) {
        std::lock_guard<std::mutex> lock(mutex_); // Lock the mutex
        if (size_ >= capacity_) throw std::runtime_error("Buffer is full"); // Check capacity
        new (&buffer_[tail_]) T(value); // Construct the object in place
        tail_ = (tail_ + 1) % capacity_; // Update tail index
        size_++; // Increment size
    }

    // Pop an element from the buffer
    T pop() {
        std::lock_guard<std::mutex> lock(mutex_); // Lock the mutex
        if (size_ == 0) throw std::runtime_error("Buffer is empty"); // Check if empty
        T value = buffer_[head_]; // Get the element at the head
        buffer_[head_].~T(); // Destroy the object
        head_ = (head_ + 1) % capacity_; // Update head index
        size_--; // Decrement size
        return value; // Return the popped value
    }

    // Get the current size of the buffer
    std::size_t size() const {
        return size_;
    }

private:
    BaseAllocator* allocator_; // Pointer to the base allocator
    std::size_t capacity_;     // Maximum capacity of the buffer
    std::size_t size_;         // Current number of elements in the buffer
    std::size_t head_;         // Index of the first element
    std::size_t tail_;         // Index of the next free slot
    T* buffer_;                // Pointer to the buffer memory
    std::mutex mutex_;         // Mutex for thread-safe access
};

// Example usage
int main() {
    // Create a debug allocator
    DebugAllocator debug_allocator;

    // Wrap the debug allocator in a type-erased allocator for int
    TypeErasedAllocator<int> int_allocator(&debug_allocator);

    // Use the type-erased allocator with std::vector
    std::vector<int, TypeErasedAllocator<int>> vec(int_allocator);
    vec.push_back(42);
    vec.push_back(100);

    // Use the type-erased allocator with std::list
    std::list<int, TypeErasedAllocator<int>> lst(int_allocator);
    lst.push_back(10);
    lst.push_back(20);

    // Use the type-erased allocator with std::map
    using MapAllocator = TypeErasedAllocator<std::pair<const int, std::string>>;
    MapAllocator map_allocator(&debug_allocator);
    std::map<int, std::string, std::less<int>, MapAllocator> map(std::less<int>(), map_allocator);
    map[1] = "one";
    map[2] = "two";

    // Create a buffer FIFO with a capacity of 10 integers
    BufferFIFO<int> buffer(&debug_allocator, 10);
    buffer.push(42);
    buffer.push(100);
    std::cout << "Popped: " << buffer.pop() << "\n";
    std::cout << "Popped: " << buffer.pop() << "\n";

    return 0;
}
