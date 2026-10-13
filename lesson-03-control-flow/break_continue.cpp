#include <iostream>

// break: выход из цикла. continue: пропуск итерации.

int main() {
    // break: остановиться на 5
    std::cout << "=== break ===\n";
    for (int i = 0; i < 10; ++i) {
        if (i == 5) break;
        std::cout << i << " ";
    }
    std::cout << "\n\n";

    // continue: пропустить чётные
    std::cout << "=== continue ===\n";
    for (int i = 0; i < 10; ++i) {
        if (i % 2 == 0) continue;
        std::cout << i << " ";
    }
    std::cout << "\n\n";

    // break во вложенном цикле — выходит только из внутреннего
    std::cout << "=== break во вложенном цикле ===\n";
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (j == 1) break;      // выход из внутреннего
            std::cout << i << "," << j << " ";
        }
        std::cout << "\n";
    }

    // Поиск в массиве: break как «нашли — выходим»
    std::cout << "\n=== Поиск ===\n";
    int arr[] = {3, 7, 1, 9, 4, 6};
    int target = 9;
    bool found = false;

    for (int x : arr) {
        if (x == target) {
            found = true;
            break;
        }
    }
    std::cout << "Элемент " << target
              << (found ? " найден" : " не найден") << "\n";

    return 0;
}
