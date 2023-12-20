// Name of the file: 10-vector.cpp 
// Name of the programmer: Igor Minenko
// Course: Programming in C++ NPRG041
// 
// Program's purpose:
// Implementing: Move constructor + Custom << operator + Custom iterator for FluidVector

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

    FluidVector(FluidVector&& other) noexcept
        : blocks_(std::move(other.blocks_)), size_(other.size_), capacity_(other.capacity_)
    {
        other.size_ = 0;
        other.capacity_ = 0;
    }

    FluidVector& operator=(FluidVector&& other) noexcept
    {
        if (this != &other)
        {
            blocks_ = std::move(other.blocks_);
            size_ = other.size_;
            capacity_ = other.capacity_;
            other.size_ = 0;
            other.capacity_ = 0;
        }
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& stream, const FluidVector& container)
    {
        for (std::size_t i = 0; i < container.size_; ++i)
        {
            if (i > 0) stream << ", ";
            stream << container[i];
        }
        return stream;
    }

    class iterator
    {
    public:
        iterator(FluidVector& container, std::size_t index) : container_(container), index_(index) {}

        T& operator*() { return container_[index_]; }

        bool operator!=(const iterator& other) const { return index_ != other.index_; }

        iterator& operator++()
        {
            ++index_;
            return *this;
        }

    private:
        FluidVector& container_;
        std::size_t index_;
    };

    iterator begin() { return iterator(*this, 0); }
    iterator end() { return iterator(*this, size_); }

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

    std::cout << "\nIterating with for loop and iterators:" << std::endl;
    for (auto iter = observers.begin(); iter != observers.end(); ++iter)
    {
        std::cout << (*iter).index << std::endl;
    }

    std::cout << "\nIterating with range-based for loop:" << std::endl;
    for (auto&& item : observers)
    {
        std::cout << item.index << std::endl;
    }

    return 0;
}
