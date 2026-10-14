#include <iostream>
#include <cstring>
#include <utility>

// Правило пяти: деструктор, копирование, присваивание, move ×2.

class Buffer {
private:
    char* data_;
    std::size_t size_;

public:
    // Конструктор
    explicit Buffer(std::size_t n)
        : data_(new char[n]), size_(n) {
        std::memset(data_, 0, n);
        std::cout << "  [Buffer ctor " << size_ << "]\n";
    }

    // 1. Деструктор
    ~Buffer() {
        std::cout << "  [Buffer dtor]\n";
        delete[] data_;
    }

    // 2. Копирующий конструктор
    Buffer(const Buffer& o)
        : data_(new char[o.size_]), size_(o.size_) {
        std::memcpy(data_, o.data_, size_);
        std::cout << "  [Buffer copy ctor]\n";
    }

    // 3. Копирующее присваивание
    Buffer& operator=(const Buffer& o) {
        std::cout << "  [Buffer copy assign]\n";
        if (this != &o) {
            delete[] data_;
            size_ = o.size_;
            data_ = new char[size_];
            std::memcpy(data_, o.data_, size_);
        }
        return *this;
    }

    // 4. Move-конструктор
    Buffer(Buffer&& o) noexcept
        : data_(o.data_), size_(o.size_) {
        std::cout << "  [Buffer move ctor]\n";
        o.data_ = nullptr;
        o.size_ = 0;
    }

    // 5. Move-присваивание
    Buffer& operator=(Buffer&& o) noexcept {
        std::cout << "  [Buffer move assign]\n";
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
    return Buffer(n);   // move / copy elision
}

int main() {
    std::cout << "=== Создание ===\n";
    Buffer a(10);

    std::cout << "\n=== Копирование ===\n";
    Buffer b = a;

    std::cout << "\n=== Move ===\n";
    Buffer c = std::move(a);
    std::cout << "  a.size() = " << a.size() << " (перемещён)\n";
    std::cout << "  c.size() = " << c.size() << "\n";

    std::cout << "\n=== Возврат из функции ===\n";
    Buffer d = make_buffer(20);

    std::cout << "\n=== Конец программы ===\n";

    return 0;
}
