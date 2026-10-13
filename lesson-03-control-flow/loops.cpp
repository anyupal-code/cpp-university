#include <iostream>

// Три вида циклов: while, do-while, for.

int main() {
    // while: проверка до тела
    std::cout << "=== while ===\n";
    int i = 0;
    while (i < 5) {
        std::cout << i << " ";
        ++i;
    }
    std::cout << "\n\n";

    // do-while: проверка после тела
    std::cout << "=== do-while (валидация ввода) ===\n";
    int x;
    do {
        std::cout << "Введите число > 0: ";
        std::cin >> x;
    } while (x <= 0);
    std::cout << "Принято: " << x << "\n\n";

    // for: счётчик
    std::cout << "=== for ===\n";
    for (int j = 0; j < 5; ++j) {
        std::cout << j << " ";
    }
    std::cout << "\n\n";

    // for с обратным счётом
    std::cout << "=== for (обратный) ===\n";
    for (int j = 5; j > 0; --j) {
        std::cout << j << " ";
    }
    std::cout << "\n\n";

    // вложенный for: таблица умножения 3x3
    std::cout << "=== таблица умножения 3x3 ===\n";
    for (int a = 1; a <= 3; ++a) {
        for (int b = 1; b <= 3; ++b) {
            std::cout << a * b << "\t";
        }
        std::cout << "\n";
    }

    return 0;
}