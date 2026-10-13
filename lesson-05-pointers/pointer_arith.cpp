#include <iostream>

// Арифметика указателей: p + n, p - n, p[i], разница указателей.

int main() {
    int arr[5] = {10, 20, 30, 40, 50};
    int* p = arr;

    std::cout << "=== Доступ через +n ===\n";
    for (int i = 0; i < 5; ++i) {
        std::cout << "*(p + " << i << ") = " << *(p + i) << "\n";
    }

    std::cout << "\n=== Инкремент указателя ===\n";
    int* q = arr;
    while (q < arr + 5) {
        std::cout << *q << " ";
        ++q;
    }
    std::cout << "\n";

    std::cout << "\n=== Адреса и размер шага ===\n";
    std::cout << "p       = " << p << "\n";
    std::cout << "p + 1   = " << (p + 1) << "\n";
    std::cout << "Разница адресов (байт): "
              << ((char*)(p + 1) - (char*)p) << "\n";
    std::cout << "sizeof(int) = " << sizeof(int) << "\n";

    std::cout << "\n=== Разница указателей ===\n";
    int* a = &arr[0];
    int* b = &arr[3];
    std::cout << "b - a = " << (b - a) << " (элементов между)\n";

    return 0;
}
