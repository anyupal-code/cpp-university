#include <iostream>
#include <stdexcept>
#include <string>

// Базовый try / catch.

double divide(double a, double b) {
    if (b == 0.0) {
        throw std::invalid_argument("Деление на ноль");
    }
    return a / b;
}

int main() {
    std::cout << "=== Успешное деление ===\n";
    try {
        std::cout << "10 / 3 = " << divide(10, 3) << "\n";
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
    }

    std::cout << "\n=== Деление на ноль ===\n";
    try {
        std::cout << "10 / 0 = " << divide(10, 0) << "\n";
        std::cout << "Эта строка не выполнится\n";
    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
    }

    std::cout << "\nПрограмма продолжает работу\n";

    return 0;
}
