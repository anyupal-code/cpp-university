#include <iostream>

// Базовые формы if / else / else if.

int main() {
    int x;
    std::cout << "Введите число: ";
    std::cin >> x;

    if (x > 0) {
        std::cout << "Положительное\n";
    } else if (x < 0) {
        std::cout << "Отрицательное\n";
    } else {
        std::cout << "Ноль\n";
    }

    // Логические операторы
    if (x > 0 && x < 10) {
        std::cout << "Однозначное положительное\n";
    }

    if (x < -100 || x > 100) {
        std::cout << "Большое по модулю\n";
    }

    // Краткая форма без else
    if (x % 2 == 0) {
        std::cout << "Чётное\n";
    }

    return 0;
}