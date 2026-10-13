#include <iostream>
#include <vector>
#include <string>

// Range-based for: обход контейнеров.

int main() {
    // Массив C-стиля
    int arr[] = {10, 20, 30, 40, 50};

    std::cout << "=== Массив ===\n";
    for (int x : arr) {
        std::cout << x << " ";
    }
    std::cout << "\n\n";

    // Изменение через ссылку
    std::cout << "=== Удвоение через ссылку ===\n";
    for (int& x : arr) {
        x *= 2;
    }
    for (int x : arr) {
        std::cout << x << " ";
    }
    std::cout << "\n\n";

    // vector
    std::vector<std::string> names = {"Иван", "Мария", "Пётр"};

    std::cout << "=== vector ===\n";
    for (const auto& name : names) {
        std::cout << name << "\n";
    }

    return 0;
}