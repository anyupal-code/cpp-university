#include <iostream>

// inline, constexpr, auto для возврата.

inline int square(int x) {
    return x * x;
}

constexpr int cube(int x) {
    return x * x * x;
}

auto multiply(int a, int b) {
    return a * b;
}

auto divide(int a, int b) -> double {
    return static_cast<double>(a) / b;
}

int main() {
    std::cout << "square(5) = " << square(5) << "\n";

    // constexpr вычисляется на этапе компиляции
    constexpr int c = cube(3);
    std::cout << "cube(3)   = " << c << "\n";

    std::cout << "multiply(4, 7) = " << multiply(4, 7) << "\n";
    std::cout << "divide(7, 2)   = " << divide(7, 2) << "\n";

    // Массив, размер которого известен на этапе компиляции
    int arr[cube(2)];   // 8 элементов
    std::cout << "Размер массива: " << sizeof(arr) / sizeof(int) << "\n";

    return 0;
}
