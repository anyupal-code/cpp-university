#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

// Алгоритмы STL для vector.

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
    std::vector<int> v = {5, 2, 8, 1, 9, 3, 7, 4, 6};

    std::cout << "Исходный: "; print(v);
    std::cout << "Размер: " << v.size() << "\n\n";

    // Сумма
    int sum = std::accumulate(v.begin(), v.end(), 0);
    std::cout << "Сумма: " << sum << "\n";

    // Мин / макс
    std::cout << "Мин:  " << *std::min_element(v.begin(), v.end()) << "\n";
    std::cout << "Макс: " << *std::max_element(v.begin(), v.end()) << "\n\n";

    // Сортировка
    std::sort(v.begin(), v.end());
    std::cout << "Сорт. возрастание:  "; print(v);

    std::sort(v.begin(), v.end(), std::greater<>{});
    std::cout << "Сорт. убывание:     "; print(v);

    // Реверс
    std::reverse(v.begin(), v.end());
    std::cout << "После reverse:      "; print(v);
    std::cout << "\n";

    // Поиск
    int target = 7;
    auto it = std::find(v.begin(), v.end(), target);
    if (it != v.end()) {
        std::cout << "Найдено " << target
                  << " на позиции " << (it - v.begin()) << "\n";
    } else {
        std::cout << target << " не найдено\n";
    }

    // Удалить все чётные (C++20)
    std::vector<int> v2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::cout << "\nДо erase_if:     "; print(v2);
    std::erase_if(v2, [](int x) { return x % 2 == 0; });
    std::cout << "После erase_if:  "; print(v2);

    return 0;
}
