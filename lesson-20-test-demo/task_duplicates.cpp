#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <algorithm>

// Задача 1. Уникальные элементы и дубликаты.

template <typename T>
void print(const std::vector<T>& v) {
    std::cout << "[";
    for (std::size_t i = 0; i < v.size(); ++i) {
        std::cout << v[i];
        if (i + 1 < v.size()) std::cout << ", ";
    }
    std::cout << "]";
}

int main() {
    std::vector<int> data = {1, 3, 5, 3, 2, 1, 7, 5, 9, 3, 8, 1};

    std::cout << "Данные: "; print(data); std::cout << "\n\n";

    // Способ 1: unordered_map — частоты за один проход
    std::unordered_map<int, int> freq;
    for (int x : data) ++freq[x];

    // Уникальные и дубликаты
    std::vector<int> unique_vals;
    std::vector<int> dup_vals;

    for (const auto& [value, count] : freq) {
        unique_vals.push_back(value);
        if (count > 1) dup_vals.push_back(value);
    }

    std::sort(unique_vals.begin(), unique_vals.end());
    std::sort(dup_vals.begin(), dup_vals.end());

    std::cout << "Уникальные:        "; print(unique_vals); std::cout << "\n";
    std::cout << "Дубликаты:         "; print(dup_vals); std::cout << "\n";
    std::cout << "Уникальных:        " << unique_vals.size() << "\n\n";

    // Способ 2: set — коротко
    std::set<int> s(data.begin(), data.end());
    std::cout << "Через set:         ";
    for (int x : s) std::cout << x << " ";
    std::cout << "\n";

    // Способ 3: подробная статистика
    std::cout << "\n=== Частоты ===\n";
    std::vector<std::pair<int, int>> items(freq.begin(), freq.end());
    std::sort(items.begin(), items.end());

    for (const auto& [value, count] : items) {
        std::cout << "  " << value << ": " << count << "\n";
    }

    return 0;
}