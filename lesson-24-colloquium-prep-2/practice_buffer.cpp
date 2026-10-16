#include <iostream>
#include <cstring>
#include <utility>
#include <stdexcept>
#include <algorithm>

// Задача 2. Класс Buffer с правилом пяти.

class Buffer {
private:
    int* data_;
    std::size_t size_;

public:
    // Конструктор
    explicit Buffer(std::size_t n)
        : data_(new int[n]), size_(n) {
        std::fill(data_, data_ + size_, 0);
    }

    // Деструктор
    ~Buffer() {
        delete[] data_;
    }

    // Копирующий конструктор — глубокое копирование
    Buffer(const Buffer& o)
        : data_(new int[o.size_]), size_(o.size_) {
        std::copy(o.data_, o.data_ + size_, data_);
    }

    // Копирующее присваивание
    Buffer& operator=(const Buffer& o) {
        if (this != &o) {
            delete[] data_;
            size_ = o.size_;
            data_ = new int[size_];
            std::copy(o.data_, o.data_ + size_, data_);
        }
        return *this;
    }

    // Move-конструктор
    Buffer(Buffer&& o) noexcept
        : data_(o.data_), size_(o.size_) {
        o.data_ = nullptr;
        o.size_ = 0;
    }

    // Move-присваивание
    Buffer& operator=(Buffer&& o) noexcept {
        if (this != &o) {
            delete[] data_;
            data_ = o.data_;
            size_ = o.size_;
            o.data_ = nullptr;
            o.size_ = 0;
        }
        return *this;
    }

    // operator[] с проверкой
    int& operator[](std::size_t i) {
        if (i >= size_) throw std::out_of_range("index");
        return data_[i];
    }

    const int& operator[](std::size_t i) const {
        if (i >= size_) throw std::out_of_range("index");
        return data_[i];
    }

    std::size_t size() const { return size_; }

    // operator== — поэлементное сравнение
    bool operator==(const Buffer& o) const {
        if (size_ != o.size_) return false;
        for (std::size_t i = 0; i < size_; ++i) {
            if (data_[i] != o.data_[i]) return false;
        }
        return true;
    }

    void print() const {
        std::cout << "[";
        for (std::size_t i = 0; i < size_; ++i) {
            std::cout << data_[i];
            if (i + 1 < size_) std::cout << ", ";
        }
        std::cout << "]\n";
    }
};

int main() {
    std::cout << "=== Создание ===\n";
    Buffer a(5);
    for (std::size_t i = 0; i < a.size(); ++i) {
        a[i] = static_cast<int>(i * 10);
    }
    std::cout << "a = "; a.print();

    std::cout << "\n=== Копирование (глубокое) ===\n";
    Buffer b = a;
    b[0] = 999;
    std::cout << "a = "; a.print();
    std::cout << "b = "; b.print();
    std::cout << "(a не изменилось — глубокое копирование)\n";

    std::cout << "\n=== Move ===\n";
    Buffer c = std::move(a);
    std::cout << "После move:\n";
    std::cout << "  a.size() = " << a.size() << " (перемещён)\n";
    std::cout << "  c = "; c.print();

    std::cout << "\n=== operator== ===\n";
    Buffer d(5);
    for (std::size_t i = 0; i < d.size(); ++i) d[i] = static_cast<int>(i * 10);
    std::cout << "d = "; d.print();
    std::cout << "b == d? " << (b == d) << "\n";
    std::cout << "c == d? " << (c == d) << "\n";

    std::cout << "\n=== Проверка границ ===\n";
    try {
        c[100] = 5;
    } catch (const std::out_of_range& e) {
        std::cout << "Поймано: " << e.what() << "\n";
    }

    return 0;
}