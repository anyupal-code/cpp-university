#include <iostream>
#include <cstring>
#include <algorithm>

// Правило трёх: деструктор + копирующий конструктор + присваивание.

class MyString {
private:
    char* data_;
    std::size_t size_;

public:
    // Конструктор
    MyString(const char* s) {
        size_ = std::strlen(s);
        data_ = new char[size_ + 1];
        std::strcpy(data_, s);
    }

    // 1. Деструктор
    ~MyString() {
        delete[] data_;
    }

    // 2. Копирующий конструктор
    MyString(const MyString& other) {
        size_ = other.size_;
        data_ = new char[size_ + 1];
        std::strcpy(data_, other.data_);
    }

    // 3. Оператор присваивания
    MyString& operator=(const MyString& other) {
        if (this == &other) return *this;   // самоприсваивание

        delete[] data_;                     // освободить старое
        size_ = other.size_;
        data_ = new char[size_ + 1];
        std::strcpy(data_, other.data_);
        return *this;
    }

    const char* c_str() const { return data_; }
};

int main() {
    MyString a("Hello");
    MyString b("World");

    std::cout << "a = " << a.c_str() << "\n";
    std::cout << "b = " << b.c_str() << "\n\n";

    b = a;   // копирующее присваивание
    std::cout << "После b = a:\n";
    std::cout << "  a = " << a.c_str() << "\n";
    std::cout << "  b = " << b.c_str() << "\n\n";

    a = a;   // самоприсваивание — должно работать
    std::cout << "После a = a: " << a.c_str() << "\n";

    return 0;
}
