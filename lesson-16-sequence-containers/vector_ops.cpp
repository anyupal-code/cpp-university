#include <iostream>
#include <vector>
#include <algorithm>

// Основные операции vector.

template <typename T>
void print(const std::vector<T>& v) {
    std::cout << "[";
    for (std::size_t i = 0; i < v.size(); ++i) {
        std::cout << v[i];
        if (i + 1 < v.size()) std::cout << ", ";
    }
    std::cout << "]\n";
}

int main() {
    std::vector<int> v;

    std::cout << "=== Добавление ===\n";
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    std::cout << "v = "; print(v);

    std::cout << "\n=== insert ===\n";
    v.insert(v.begin() + 1, 15);
    std::cout << "После insert(1, 15): "; print(v);

    v.insert(v.begin(), 5);
    std::cout << "После insert(begin, 5): "; print(v);

    std::cout << "\n=== erase ===\n";
    v.erase(v.begin() + 2);
    std::cout << "После erase(2): "; print(v);

    v.erase(v.begin(), v.begin() + 2);
    std::cout << "После erase(0, 2): "; print(v);

    std::cout << "\n=== pop_back ===\n";
    v.pop_back();
    std::cout << "После pop_back: "; print(v);

    std::cout << "\n=== Доступ ===\n";
    std::cout << "v[0] = " << v[0] << "\n";
    std::cout << "v.at(0) = " << v.at(0) << "\n";
    std::cout << "v.front() = " << v.front() << "\n";
    std::cout << "v.back() = " << v.back() << "\n";

    std::cout << "\n=== Поиск и сортировка ===\n";
    v = {5, 2, 8, 1, 9, 3};
    std::cout << "Исходный: "; print(v);

    std::sort(v.begin(), v.end());
    std::cout << "Отсорт.:  "; print(v);

    auto it = std::find(v.begin(), v.end(), 5);
    if (it != v.end()) {
        std::cout << "Найдено 5 на позиции " << (it - v.begin()) << "\n";
    }

    std::cout << "\n=== Обход ===\n";
    std::cout << "Индексный:    ";
    for (std::size_t i = 0; i < v.size(); ++i) std::cout << v[i] << " ";
    std::cout << "\n";

    std::cout << "Range-based:  ";
    for (int x : v) std::cout << x << " ";
    std::cout << "\n";

    std::cout << "Итераторы:    ";
    for (auto it2 = v.begin(); it2 != v.end(); ++it2) std::cout << *it2 << " ";
    std::cout << "\n";

    return 0;
}
