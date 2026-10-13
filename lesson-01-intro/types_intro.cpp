#include <iostream>

// Основные типы данных и их размеры.

int main() {
    int i = 42;
    double d = 3.14;
    bool flag = true;
    char c = 'A';

    std::cout << "int:    " << i << ", размер: " << sizeof(int) << " байт\n";
    std::cout << "double: " << d << ", размер: " << sizeof(double) << " байт\n";
    std::cout << "bool:   " << flag << ", размер: " << sizeof(bool) << " байт\n";
    std::cout << "char:   " << c << ", размер: " << sizeof(char) << " байт\n";

    std::cout << "\nСписковая инициализация:\n";
    int x{5};
    double y{2.71};
    std::cout << "x = " << x << ", y = " << y << "\n";

    std::cout << "\nauto выводит тип:\n";
    auto a = 10;         // int
    auto b = 3.14;       // double
    auto ch = 'Z';       // char
    std::cout << "a = " << a << ", b = " << b << ", ch = " << ch << "\n";

    return 0;
}