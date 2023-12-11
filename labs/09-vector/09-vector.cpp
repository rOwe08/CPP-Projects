// Name of the file: 09-vector.cpp 
// Name of the programmer: Igor Minenko
// Course: Programming in C++ NPRG041
// 
// Program's purpose:
// Creating a generic rubber field as a container that preserves the order of the inserted elements.

#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>

template <typename T, std::size_t BLOCK_SIZE>
class FluidVector
{
public:
    FluidVector() : size_(0), capacity_(0) {}

    FluidVector(const FluidVector&) = delete;
    FluidVector& operator=(const FluidVector&) = delete;

    void push_back(T&& value)
    {
        if (size_ == capacity_)
        {
            allocateNewBlock();
        }
        std::size_t blockIndex = size_ / BLOCK_SIZE;
        std::size_t indexInBlock = size_ % BLOCK_SIZE;
        blocks_[blockIndex][indexInBlock] = std::move(value);
        size_++;
    }

    T& operator[](std::size_t index)
    {
        std::size_t blockIndex = index / BLOCK_SIZE;
        std::size_t indexInBlock = index % BLOCK_SIZE;
        return blocks_[blockIndex][indexInBlock];
    }

    const T& operator[](std::size_t index) const
    {
        std::size_t blockIndex = index / BLOCK_SIZE;
        std::size_t indexInBlock = index % BLOCK_SIZE;
        return blocks_[blockIndex][indexInBlock];
    }

    std::size_t size() const
    {
        return size_;
    }

    std::size_t capacity() const
    {
        return capacity_;
    }

private:
    std::vector<std::unique_ptr<T[]>> blocks_;
    std::size_t size_;
    std::size_t capacity_;

    void allocateNewBlock()
    {
        blocks_.emplace_back(std::make_unique<T[]>(BLOCK_SIZE));
        capacity_ += BLOCK_SIZE;
    }
};

struct Observer
{
    int index;
    Observer() : index(-1) { std::cout << "ctor -1" << std::endl; }
    Observer(int index_) : index(index_) { std::cout << "ctor " << index << std::endl; }
    // Rule of five.
    Observer(const Observer& other) : index(other.index) { std::cout << "copy " << index << std::endl; }
    Observer(Observer&& other) noexcept : index(other.index) { other.index = -1; std::cout << "move " << index << std::endl; }
    void operator=(const Observer& other) { index = other.index; std::cout << "= copy " << index << std::endl; }
    void operator=(Observer&& other) noexcept { index = other.index;  other.index = -1; std::cout << "= move " << index << std::endl; }
    ~Observer() { std::cout << "dtor " << index << std::endl; }
};

int main()
{
    FluidVector<Observer, 2> observers;

    observers.push_back(Observer(1));
    observers.push_back(Observer(2));
    observers.push_back(Observer(3));

    std::cout << "Observer at index 1 has index: " << observers[1].index << std::endl;
    std::cout << "Size: " << observers.size() << ", Capacity: " << observers.capacity() << std::endl;

    return 0;
}
