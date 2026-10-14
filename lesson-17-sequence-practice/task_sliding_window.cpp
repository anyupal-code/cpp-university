#include <iostream>
#include <vector>
#include <deque>

// Задача 3. Максимум в скользящем окне размера K.
// Решение через монотонную deque: O(n).

std::vector<int> max_sliding_window(const std::vector<int>& arr, int k) {
    std::vector<int> result;
    std::deque<int> dq;    // индексы, значения по убыванию

    for (int i = 0; i < static_cast<int>(arr.size()); ++i) {
        // Убираем с начала индексы, вышедшие из окна
        while (!dq.empty() && dq.front() <= i - k) {
            dq.pop_front();
        }

        // Убираем с конца элементы, меньшие нового
        while (!dq.empty() && arr[dq.back()] < arr[i]) {
            dq.pop_back();
        }

        dq.push_back(i);

        // Когда окно заполнено — записываем максимум
        if (i >= k - 1) {
            result.push_back(arr[dq.front()]);
        }
    }

    return result;
}

void print(const std::vector<int>& v) {
    std::cout << "[";
    for (std::size_t i = 0; i < v.size(); ++i) {
        std::cout << v[i];
        if (i + 1 < v.size()) std::cout << ", ";
    }
    std::cout << "]\n";
}

int main() {
    std::vector<int> arr = {1, 3, -1, -3, 5, 3, 6, 7};
    int k = 3;

    std::cout << "Массив: "; print(arr);
    std::cout << "Окно: " << k << "\n\n";

    auto result = max_sliding_window(arr, k);
    std::cout << "Максимумы по окнам: "; print(result);

    // Сравнение с наивным решением
    std::cout << "\nНаивный метод:\n";
    for (int i = k - 1; i < static_cast<int>(arr.size()); ++i) {
        int mx = arr[i];
        for (int j = i - k + 1; j <= i; ++j) {
            if (arr[j] > mx) mx = arr[j];
        }
        std::cout << "  окно [" << i - k + 1 << ".." << i << "]: " << mx << "\n";
    }

    return 0;
}
