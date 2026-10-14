#include <iostream>
#include <cstring>

// Копирующий конструктор: глубокое копирование.

class MyString {
private:
    char* data_;
    std::size_t size_;

public:
    MyString(const char* s) {
        size_ = std::strlen(s);
        data_ = new char[size_ + 1];
        std::strcpy(data_, s);
    }

    // Копирующий конструктор
    MyString(const MyString& other) {
        std::cout << "  [копирующий конструктор]\n";
        size_ = other.size_;
        data_ = new char[size_ + 1];
        std::strcpy(data_, other.data_);
    }

    // Деструктор
    ~MyString() {
        delete[] data_;
    }

    const char* c_str() const { return data_; }
};

void print(MyString s) {   // копирование при передаче
    std::cout << "  внутри print: " << s.c_str() << "\n";
}

int main() {
    MyString a("Hello");
    std::cout << "a = " << a.c_str() << "\n\n";

    std::cout << "Копирование:\n";
    MyString b = a;
    std::cout << "b = " << b.c_str() << "\n\n";

    std::cout << "Передача по значению:\n";
    print(a);

    return 0;
}
