#include <iostream>
#include <algorithm>
#include <numeric>
#include <iterator>

// Типичные алгоритмы на массивах.

int main() {
    int arr[] = {5, 2, 8, 1, 9, 3, 7, 4, 6};
    const std::size_t n = std::size(arr);

    std::cout << "Массив: ";
    for (int x : arr) std::cout << x << " ";
    std::cout << "\n\n";

    // Сумма
    int sum = 0;
    for (int x : arr) sum += x;
    std::cout << "Сумма (руками):    " << sum << "\n";
    std::cout << "Сумма (accumulate): "
              << std::accumulate(std::begin(arr), std::end(arr), 0) << "\n";

    // Среднее
    double avg = static_cast<double>(sum) / n;
    std::cout << "Среднее: " << avg << "\n\n";

    // Мин и макс — вручную
    int mn = arr[0], mx = arr[0];
    for (std::size_t i = 1; i < n; ++i) {
        if (arr[i] < mn) mn = arr[i];
        if (arr[i] > mx) mx = arr[i];
    }
    std::cout << "Мин (руками): " << mn << "\n";
    std::cout << "Макс (руками): " << mx << "\n";

    // Через STL
    std::cout << "Мин (STL):    " << *std::min_element(arr, arr + n) << "\n";
    std::cout << "Макс (STL):   " << *std::max_element(arr, arr + n) << "\n\n";

    // Поиск
    int target = 8;
    int* found = std::find(arr, arr + n, target);
    if (found != arr + n) {
        std::cout << "Найдено " << target
                  << " на позиции " << (found - arr) << "\n";
    }

    // Реверс копии
    int copy[n];
    std::copy(arr, arr + n, copy);
    std::reverse(copy, copy + n);
    std::cout << "Реверс: ";
    for (int x : copy) std::cout << x << " ";
    std::cout << "\n";

    // Сортировка копии
    std::copy(arr, arr + n, copy);
    std::sort(copy, copy + n);
    std::cout << "Сорт.:  ";
    for (int x : copy) std::cout << x << " ";
    std::cout << "\n";

    return 0;
}
