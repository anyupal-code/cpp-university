#include <iostream>
#include <array>
#include <algorithm>

// std::array: фиксированный размер, методы STL.

int main() {
    std::array<int, 5> arr = {10, 20, 30, 40, 50};

    std::cout << "=== Свойства ===\n";
    std::cout << "size:     " << arr.size() << "\n";
    std::cout << "empty:    " << arr.empty() << "\n";
    std::cout << "front:    " << arr.front() << "\n";
    std::cout << "back:     " << arr.back() << "\n";
    std::cout << "max_size: " << arr.max_size() << "\n";

    std::cout << "\n=== Доступ ===\n";
    std::cout << "arr[0]    = " << arr[0] << "\n";
    std::cout << "arr.at(2) = " << arr.at(2) << "\n";

    std::cout << "\n=== Обход ===\n";
    std::cout << "Элементы: ";
    for (int x : arr) std::cout << x << " ";
    std::cout << "\n";

    std::cout << "\n=== Сортировка ===\n";
    std::array<int, 5> s = {5, 2, 8, 1, 9};
    std::sort(s.begin(), s.end());
    std::cout << "Отсорт.: ";
    for (int x : s) std::cout << x << " ";
    std::cout << "\n";

    std::cout << "\n=== fill ===\n";
    std::array<int, 5> z;
    z.fill(0);
    std::cout << "zeros: ";
    for (int x : z) std::cout << x << " ";
    std::cout << "\n";

    std::cout << "\n=== Сравнение ===\n";
    std::array<int, 3> a = {1, 2, 3};
    std::array<int, 3> b = {1, 2, 4};
    std::cout << "a == b? " << (a == b) << "\n";
    std::cout << "a <  b? " << (a <  b) << "\n";

    return 0;
}
