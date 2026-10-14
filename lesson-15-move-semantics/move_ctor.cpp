#include <iostream>
#include <cstring>
#include <utility>
#include <vector>

// Move-конструктор vs copy.

class Buffer {
private:
    char* data_;
    std::size_t size_;

public:
    explicit Buffer(std::size_t n)
        : data_(new char[n]), size_(n) {
        std::memset(data_, 0, n);
        std::cout << "  [ctor " << n << "]\n";
    }

    // Копирующий конструктор
    Buffer(const Buffer& o)
        : data_(new char[o.size_]), size_(o.size_) {
        std::memcpy(data_, o.data_, size_);
        std::cout << "  [COPY ctor " << size_ << " байт]\n";
    }

    // Move-конструктор
    Buffer(Buffer&& o) noexcept
        : data_(o.data_), size_(o.size_) {
        o.data_ = nullptr;
        o.size_ = 0;
        std::cout << "  [MOVE ctor " << size_ << " байт]\n";
    }

    ~Buffer() {
        delete[] data_;
    }

    std::size_t size() const { return size_; }
};

Buffer make_buffer(std::size_t n) {
    Buffer b(n);
    return b;   // NRVO — без copy/move
}

int main() {
    std::cout << "=== Создание ===\n";
    Buffer a(100);

    std::cout << "\n=== Копирование ===\n";
    Buffer b = a;                   // copy

    std::cout << "\n=== Move ===\n";
    Buffer c = std::move(a);        // move
    std::cout << "  a.size() = " << a.size() << " (перемещён)\n";
    std::cout << "  c.size() = " << c.size() << "\n";

    std::cout << "\n=== Возврат из функции ===\n";
    Buffer d = make_buffer(200);    // NRVO, ни copy, ни move

    std::cout << "\n=== vector.push_back ===\n";
    std::vector<Buffer> v;
    v.reserve(3);
    v.push_back(Buffer(10));        // move (временный)
    v.push_back(std::move(b));      // move (явный)

    std::cout << "\n=== Конец ===\n";

    return 0;
}
