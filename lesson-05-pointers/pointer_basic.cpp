#include <iostream>

// Основы указателей: & (взять адрес), * (разыменовать), nullptr.

int main() {
    int x = 42;

    // Адрес переменной
    std::cout << "x = " << x << "\n";
    std::cout << "&x = " << &x << "\n";

    // Указатель
    int* p = &x;
    std::cout << "\np = " << p << " (тот же адрес)\n";
    std::cout << "*p = " << *p << " (значение по адресу)\n";

    // Изменение через указатель
    *p = 100;
    std::cout << "\nПосле *p = 100: x = " << x << "\n";

    // nullptr
    int* q = nullptr;
    std::cout << "\nq = " << q << " (nullptr)\n";
    std::cout << "q == nullptr? " << (q == nullptr) << "\n";

    // Размер указателя
    std::cout << "\nsizeof(int*) = " << sizeof(int*) << " байт\n";
    std::cout << "sizeof(char*) = " << sizeof(char*) << " байт\n";
    std::cout << "sizeof(double*) = " << sizeof(double*) << " байт\n";

    return 0;
}
