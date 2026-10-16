#include <iostream>
#include <vector>
#include <algorithm>

// Базовые алгоритмы: find, count, all_of, min/max.

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

    std::cout << "v = "; print(v);
    std::cout << "\n";

    // find
    auto it = std::find(v.begin(), v.end(), 8);
    if (it != v.end()) {
        std::cout << "Найдено 8 на позиции " << (it - v.begin()) << "\n";
    }

    auto missing = std::find(v.begin(), v.end(), 100);
    std::cout << "100 найдено? " << (missing != v.end()) << "\n\n";

    // count
    std::vector<int> v2 = {1, 2, 2, 3, 2, 4, 2};
    std::cout << "count(2) в v2 = " << std::count(v2.begin(), v2.end(), 2) << "\n";
    std::cout << "count_if(чётные) в v = "
              << std::count_if(v.begin(), v.end(),
                               [](int x) { return x % 2 == 0; }) << "\n\n";

    // all_of, any_of, none_of
    std::cout << "all_of(> 0)?    " << std::all_of(v.begin(), v.end(),
                                                   [](int x) { return x > 0; }) << "\n";
    std::cout << "any_of(> 8)?    " << std::any_of(v.begin(), v.end(),
                                                   [](int x) { return x > 8; }) << "\n";
    std::cout << "none_of(< 0)?   " << std::none_of(v.begin(), v.end(),
                                                    [](int x) { return x < 0; }) << "\n\n";

    // min / max
    auto mn = std::min_element(v.begin(), v.end());
    auto mx = std::max_element(v.begin(), v.end());
    std::cout << "min = " << *mn << " (позиция " << (mn - v.begin()) << ")\n";
    std::cout << "max = " << *mx << " (позиция " << (mx - v.begin()) << ")\n\n";

    // sort
    std::vector<int> s = v;
    std::sort(s.begin(), s.end());
    std::cout << "sort:          "; print(s);

    std::sort(s.begin(), s.end(), std::greater<>{});
    std::cout << "sort (убыв.):  "; print(s);

    std::sort(s.begin(), s.end(),
              [](int a, int b) { return a % 2 < b % 2; });
    std::cout << "sort (чёт.→нечёт.): "; print(s);

    return 0;
}