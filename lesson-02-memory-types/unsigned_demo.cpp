#include <iostream>

// Знаковые vs беззнаковые: подводные камни.

int main() {
    // 1. Переполнение беззнакового — циклический переход
    unsigned int u = 0;
    u--;
    std::cout << "unsigned 0 - 1 = " << u << "\n";

    // 2. Сравнение знакового с беззнаковым — знаковый превращается в беззнаковый
    int a = -1;
    unsigned int b = 1;
    std::cout << "\nint a = -1, unsigned b = 1\n";
    std::cout << "a < b? " << (a < b) << "  (неожиданно 0!)\n";
    std::cout << "static_cast<unsigned>(a) = "
              << static_cast<unsigned>(a) << "\n";

    // 3. Разница между int и unsigned int в размере — нет,
    //    но диапазон сдвигается
    std::cout << "\nРазмер int:          " << sizeof(int) << "\n";
    std::cout << "Размер unsigned int: " << sizeof(unsigned int) << "\n";

    // 4. Явное приведение — правильный способ
    int x = -5;
    unsigned int y = static_cast<unsigned int>(x);
    std::cout << "\nstatic_cast<unsigned>(-5) = " << y << "\n";

    return 0;
}