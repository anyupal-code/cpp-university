#include <iostream>
#include <vector>
#include <algorithm>

// Задача 4. Топ-K элементов тремя способами.

void print(const std::vector<int>& v) {
    std::cout << "[";
    for (std::size_t i = 0; i < v.size(); ++i) {
        std::cout << v[i];
        if (i + 1 < v.size()) std::cout << ", ";
    }
    std::cout << "]\n";
}

int main() {
    std::vector<int> data = {5, 2, 8, 1, 9, 3, 7, 4, 6, 10};
    int k = 3;

    std::cout << "Данные: "; print(data);
    std::cout << "K = " << k << "\n\n";

    // Способ 1: полная сортировка
    {
        auto v = data;
        std::sort(v.begin(), v.end(), std::greater<>());
        std::cout << "Способ 1 (sort):          ";
        for (int i = 0; i < k; ++i) std::cout << v[i] << " ";
        std::cout << "  — O(n log n)\n";
    }

    // Способ 2: partial_sort
    {
        auto v = data;
        std::partial_sort(v.begin(), v.begin() + k, v.end(),
                          std::greater<>());
        std::cout << "Способ 2 (partial_sort):  ";
        for (int i = 0; i < k; ++i) std::cout << v[i] << " ";
        std::cout << "  — O(n log k)\n";
    }

    // Способ 3: nth_element
    {
        auto v = data;
        std::nth_element(v.begin(), v.begin() + k, v.end(),
                         std::greater<>());
        std::cout << "Способ 3 (nth_element):   ";
        for (int i = 0; i < k; ++i) std::cout << v[i] << " ";
        std::cout << "  — O(n) среднее\n";
    }

    // Способ 4: поток через priority_queue (не требует весь массив в памяти)
    {
        auto v = data;
        std::priority_queue<int, std::vector<int>, std::greater<>> pq;
        for (int x : v) {
            pq.push(x);
            if (static_cast<int>(pq.size()) > k) pq.pop();
        }
        std::cout << "Способ 4 (priority_queue): ";
        std::vector<int> result;
        while (!pq.empty()) {
            result.push_back(pq.top());
            pq.pop();
        }
        std::reverse(result.begin(), result.end());
        print(result);
        std::cout << "  — O(n log k), работает при потоке\n";
    }

    return 0;
}
