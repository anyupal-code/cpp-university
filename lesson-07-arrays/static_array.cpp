#include <iostream>
#include <iterator>

// Статические массивы: объявление, инициализация, размер.

int main() {
    // Способы объявления
    int a[5];                          // неинициализирован
    int b[5] = {10, 20, 30, 40, 50};   // полностью
    int c[] = {1, 2, 3};               // размер выведен = 3
    int d[5] = {1, 2};                 // {1, 2, 0, 0, 0}
    int e[5] = {};                     // все нули

    // Размер
    std::size_t n = sizeof(b) / sizeof(b[0]);
    std::cout << "sizeof(b) = " << sizeof(b) << " байт\n";
    std::cout << "sizeof(b[0]) = " << sizeof(b[0]) << " байт\n";
    std::cout << "Элементов: " << n << "\n\n";

    // std::size (C++17)
    std::cout << "std::size(b) = " << std::size(b) << "\n\n";

    // Индексация
    std::cout << "b[0] = " << b[0] << "\n";
    std::cout << "b[4] = " << b[4] << "\n\n";

    // Обход: индексный
    std::cout << "Индексный: ";
    for (std::size_t i = 0; i < n; ++i) {
        std::cout << b[i] << " ";
    }
    std::cout << "\n";

    // Обход: range-based
    std::cout << "Range-based: ";
    for (int x : b) {
        std::cout << x << " ";
    }
    std::cout << "\n";

    // Обход: через указатель
    std::cout << "Указатель: ";
    for (int* p = b; p < b + n; ++p) {
        std::cout << *p << " ";
    }
    std::cout << "\n";

    // d — частичная инициализация
    std::cout << "\nd = ";
    for (int x : d) std::cout << x << " ";
    std::cout << "\n";

    return 0;
}
