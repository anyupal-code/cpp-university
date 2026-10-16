#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

// Числовые алгоритмы: accumulate, partial_sum, inner_product.

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
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::cout << "v = "; print(v);
    std::cout << "\n";

    // accumulate: сумма
    int sum = std::accumulate(v.begin(), v.end(), 0);
    std::cout << "Сумма:            " << sum << "\n";

    // accumulate: произведение
    int prod = std::accumulate(v.begin(), v.end(), 1,
                               std::multiplies<>());
    std::cout << "Произведение:     " << prod << " (внимание: переполнение)\n";

    // accumulate: сумма квадратов через лямбду
    int sq_sum = std::accumulate(v.begin(), v.end(), 0,
                                 [](int acc, int x) { return acc + x * x; });
    std::cout << "Сумма квадратов:  " << sq_sum << "\n\n";

    // inner_product: скалярное произведение
    std::vector<int> a = {1, 2, 3};
    std::vector<int> b = {4, 5, 6};
    int dot = std::inner_product(a.begin(), a.end(), b.begin(), 0);
    std::cout << "a = "; print(a);
    std::cout << "b = "; print(b);
    std::cout << "a · b = " << dot << " (1*4 + 2*5 + 3*6)\n\n";

    // partial_sum: префиксные суммы
    std::vector<int> prefix(v.size());
    std::partial_sum(v.begin(), v.end(), prefix.begin());
    std::cout << "Префиксные суммы: "; print(prefix);
    std::cout << "  (каждое — сумма от начала)\n\n";

    // adjacent_difference: разности соседей
    std::vector<int> diff(v.size());
    std::adjacent_difference(v.begin(), v.end(), diff.begin());
    std::cout << "Разности:         "; print(diff);

    // iota
    std::vector<int> seq(5);
    std::iota(seq.begin(), seq.end(), 100);
    std::cout << "\niota(100):        "; print(seq);

    // gcd, lcm (C++17)
    std::cout << "\ngcd(12, 18) = " << std::gcd(12, 18) << "\n";
    std::cout << "lcm(4, 6)   = " << std::lcm(4, 6) << "\n";

    return 0;
}