#include <iostream>
#include <cstring>
#include <utility>

// Move-присваивание.

class Buffer {
private:
    char* data_;
    std::size_t size_;

public:
    explicit Buffer(std::size_t n, char fill = 0)
        : data_(new char[n]), size_(n) {
        std::memset(data_, fill, n);
        std::cout << "  [ctor " << n << "]\n";
    }

    ~Buffer() {
        delete[] data_;
    }

    // Копирующий конструктор
    Buffer(const Buffer& o)
        : data_(new char[o.size_]), size_(o.size_) {
        std::memcpy(data_, o.data_, size_);
        std::cout << "  [COPY ctor " << size_ << "]\n";
    }

    // Move-конструктор
    Buffer(Buffer&& o) noexcept
        : data_(o.data_), size_(o.size_) {
        o.data_ = nullptr;
        o.size_ = 0;
        std::cout << "  [MOVE ctor " << size_ << "]\n";
    }

    // Копирующее присваивание
    Buffer& operator=(const Buffer& o) {
        std::cout << "  [COPY assign]\n";
        if (this != &o) {
            delete[] data_;
            size_ = o.size_;
            data_ = new char[size_];
            std::memcpy(data_, o.data_, size_);
        }
        return *this;
    }

    // Move-присваивание
    Buffer& operator=(Buffer&& o) noexcept {
        std::cout << "  [MOVE assign]\n";
        if (this != &o) {
            delete[] data_;
            data_ = o.data_;
            size_ = o.size_;
            o.data_ = nullptr;
            o.size_ = 0;
        }
        return *this;
    }

    std::size_t size() const { return size_; }
};

int main() {
    Buffer a(100, 'A');
    Buffer b(200, 'B');

    std::cout << "\n=== Копирующее присваивание ===\n";
    b = a;

    std::cout << "\n=== Move-присваивание ===\n";
    Buffer c(50, 'C');
    c = std::move(a);

    std::cout << "  a.size() = " << a.size() << " (перемещён)\n";
    std::cout << "  c.size() = " << c.size() << "\n";

    std::cout << "\n=== Конец ===\n";

    return 0;
}
