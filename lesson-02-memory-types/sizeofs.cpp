#include <iostream>

// Размеры основных типов данных в байтах.

int main() {
    std::cout << "=== Размеры типов (байт) ===\n";
    std::cout << "bool:        " << sizeof(bool) << "\n";
    std::cout << "char:        " << sizeof(char) << "\n";
    std::cout << "short:       " << sizeof(short) << "\n";
    std::cout << "int:         " << sizeof(int) << "\n";
    std::cout << "long:        " << sizeof(long) << "\n";
    std::cout << "long long:   " << sizeof(long long) << "\n";
    std::cout << "float:       " << sizeof(float) << "\n";
    std::cout << "double:      " << sizeof(double) << "\n";
    std::cout << "long double: " << sizeof(long double) << "\n";

    std::cout << "\n=== Размеры переменных ===\n";
    int x = 42;
    double d = 3.14;
    char c = 'A';
    std::cout << "int x:    " << sizeof(x) << "\n";
    std::cout << "double d: " << sizeof(d) << "\n";
    std::cout << "char c:   " << sizeof(c) << "\n";

    return 0;
}