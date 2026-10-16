#include <iostream>
#include <vector>
#include <unordered_map>

// Задача 4. Two Sum: найти индексы двух элементов с суммой target.

std::pair<int, int> two_sum(const std::vector<int>& arr, int target) {
    std::unordered_map<int, int> seen;   // значение -> индекс

    for (int i = 0; i < static_cast<int>(arr.size()); ++i) {
        int complement = target - arr[i];

        auto it = seen.find(complement);
        if (it != seen.end()) {
            return {it->second, i};
        }

        seen[arr[i]] = i;
    }

    return {-1, -1};   // не найдено
}

void print(const std::vector<int>& v) {
    std::cout << "[";
    for (std::size_t i = 0; i < v.size(); ++i) {
        std::cout << v[i];
        if (i + 1 < v.size()) std::cout << ", ";
    }
    std::cout << "]";
}

int main() {
    std::vector<int> arr = {2, 7, 11, 15, 3, 6, 8};
    int target = 9;

    std::cout << "Массив: "; print(arr); std::cout << "\n";
    std::cout << "Target: " << target << "\n\n";

    auto [i, j] = two_sum(arr, target);

    if (i >= 0) {
        std::cout << "Найдено: arr[" << i << "] + arr[" << j << "] = "
                  << arr[i] << " + " << arr[j] << " = " << target << "\n";
    } else {
        std::cout << "Пара не найдена\n";
    }

    // Проверка на другом массиве
    std::cout << "\n=== Второй пример ===\n";
    std::vector<int> arr2 = {3, 3};
    target = 6;
    std::cout << "Массив: "; print(arr2); std::cout << "\n";
    std::cout << "Target: " << target << "\n";

    auto [a, b] = two_sum(arr2, target);
    if (a >= 0) {
        std::cout << "Найдено: arr[" << a << "] + arr[" << b << "] = "
                  << arr2[a] << " + " << arr2[b] << " = " << target << "\n";
    } else {
        std::cout << "Пара не найдена\n";
    }

    return 0;
}