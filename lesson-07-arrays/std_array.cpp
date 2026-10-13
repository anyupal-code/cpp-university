#include <iostream>
#include <array>
#include <algorithm>

// std::array — обёртка над статическим массивом.

int main() {
    std::array<int, 5> arr = {10, 20, 30, 40, 50};

    std::cout << "Размер: " << arr.size() << "\n";
    std::cout << "Пустой? " << arr.empty() << "\n";
    std::cout << "Первый: " << arr.front() << "\n";
    std::cout << "Последний: " << arr.back() << "\n\n";

    // Доступ
    std::cout << "arr[2]    = " << arr[2] << "\n";
    std::cout << "arr.at(2) = " << arr.at(2) << "\n\n";

    // Обход
    std::cout << "Элементы: ";
    for (int x : arr) std::cout << x << " ";
    std::cout << "\n\n";

    // Сортировка
    std::sort(arr.begin(), arr.end());
    std::cout << "Отсорт.: ";
    for (int x : arr) std::cout << x << " ";
    std::cout << "\n\n";

    // Заполнение
    std::array<int, 5> zeros;
    zeros.fill(0);
    std::cout << "zeros: ";
    for (int x : zeros) std::cout << x << " ";
    std::cout << "\n";

    return 0;
}
