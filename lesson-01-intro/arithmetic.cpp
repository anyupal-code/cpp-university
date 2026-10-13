#include <iostream>

// Арифметика: деление целое и вещественное, остаток, приведение.

int main() {
    int a = 7, b = 2;

    std::cout << "a + b  = " << a + b << "\n";
    std::cout << "a - b  = " << a - b << "\n";
    std::cout << "a * b  = " << a * b << "\n";
    std::cout << "a / b  = " << a / b << " (целое деление)\n";
    std::cout << "a % b  = " << a % b << " (остаток)\n";

    std::cout << "\nВещественное деление:\n";
    double d1 = 7.0 / 2;
    double d2 = static_cast<double>(a) / b;
    std::cout << "7.0 / 2                    = " << d1 << "\n";
    std::cout << "static_cast<double>(a) / b = " << d2 << "\n";

    std::cout << "\nИнкремент и декремент:\n";
    int i = 5;
    std::cout << "i = " << i << "\n";
    i++;
    std::cout << "i++ -> " << i << "\n";
    i--;
    std::cout << "i-- -> " << i << "\n";

    return 0;
}