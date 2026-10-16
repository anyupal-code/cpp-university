#include <iostream>
#include <cstring>
#include <utility>
#include <algorithm>

// Обзор: правило пяти.

class Buffer {
private:
    int* data_;
    std::size_t size_;

public:
    // 1. Конструктор
    explicit Buffer(std::size_t n)
        : data_(new int[n]), size_(n) {
        std::fill(data_, data_ + size_, 0);
        std::cout << "  [ctor " << size_ << "]\n";
    }

    // 2. Деструктор
    ~Buffer() {
        std::cout << "  [dtor " << size_ << "]\n";
        delete[] data_;
    }

    // 3. Копирующий конструктор
    Buffer(const Buffer& o)
        : data_(new int[o.size_]), size_(o.size_) {
        std::copy(o.data_, o.data_ + size_, data_);
        std::cout << "  [copy ctor " << size_ << "]\n";
    }

    // 4. Копирующее присваивание
    Buffer& operator=(const Buffer& o) {
        std::cout << "  [copy assign]\n";
        if (this != &o) {
            delete[] data_;
            size_ = o.size_;
            data_ = new int[size_];
            std::copy(o.data_, o.data_ + size_, data_);
        }
        return *this;
    }

    // 5. Move-конструктор
    Buffer(Buffer&& o) noexcept
        : data_(o.data_), size_(o.size_) {
        o.data_ = nullptr;
        o.size_ = 0;
        std::cout << "  [move ctor]\n";
    }

    // 6. Move-присваивание
    Buffer& operator=(Buffer&& o) noexcept {
        std::cout << "  [move assign]\n";
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

Buffer make_buffer(std::size_t n) {
    return Buffer(n);
}

int main() {
    std::cout << "=== Создание ===\n";
    Buffer a(10);

    std::cout << "\n=== Копирование ===\n";
    Buffer b = a;

    std::cout << "\n=== Move ===\n";
    Buffer c = std::move(a);

    std::cout << "\n=== Возврат из функции (NRVO) ===\n";
    Buffer d = make_buffer(20);

    std::cout << "\n=== Конец ===\n";

    return 0;
}