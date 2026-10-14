#include <iostream>
#include <cstring>

// Деструктор и RAII: класс управляет динамической памятью.

class MyString {
private:
    char* data_;
    std::size_t size_;

public:
    MyString(const char* s) {
        size_ = std::strlen(s);
        data_ = new char[size_ + 1];
        std::strcpy(data_, s);
        std::cout << "  Создано: \"" << data_ << "\"\n";
    }

    ~MyString() {
        std::cout << "  Уничтожено: \"" << data_ << "\"\n";
        delete[] data_;
    }

    const char* c_str() const { return data_; }
    std::size_t size() const { return size_; }
};

int main() {
    std::cout << "=== Блок ===\n";
    {
        MyString s("Hello");
        std::cout << "  s = \"" << s.c_str() << "\", размер = " << s.size() << "\n";
    }   // здесь вызывается деструктор
    std::cout << "После блока\n";

    std::cout << "\n=== Массив ===\n";
    {
        MyString a("first");
        MyString b("second");
        std::cout << "  Оба живы\n";
    }   // деструкторы вызываются в обратном порядке

    return 0;
}
