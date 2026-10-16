#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

// transform, copy_if, fill, iota.

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
    std::vector<int> src = {1, 2, 3, 4, 5};
    std::cout << "src = "; print(src);
    std::cout << "\n";

    // transform: квадраты
    std::vector<int> squares(src.size());
    std::transform(src.begin(), src.end(), squares.begin(),
                   [](int x) { return x * x; });
    std::cout << "Квадраты:  "; print(squares);

    // transform: сумма двух диапазонов
    std::vector<int> a = {1, 2, 3};
    std::vector<int> b = {10, 20, 30};
    std::vector<int> sum(3);
    std::transform(a.begin(), a.end(), b.begin(), sum.begin(),
                   [](int x, int y) { return x + y; });
    std::cout << "a + b:     "; print(sum);

    // copy_if: только чётные
    std::vector<int> evens;
    std::copy_if(src.begin(), src.end(), std::back_inserter(evens),
                 [](int x) { return x % 2 == 0; });
    std::cout << "Чётные:    "; print(evens);

    // fill: всё нули
    std::vector<int> zeros(5);
    std::fill(zeros.begin(), zeros.end(), 0);
    std::cout << "fill(0):   "; print(zeros);

    // iota: последовательность 1..10
    std::vector<int> seq(10);
    std::iota(seq.begin(), seq.end(), 1);
    std::cout << "iota(1):   "; print(seq);

    // generate: свои значения
    std::vector<int> powers(8);
    int p = 1;
    std::generate(powers.begin(), powers.end(),
                  [&p]() { p *= 2; return p; });
    std::cout << "generate:  "; print(powers);

    // remove + erase: удалить все 3
    std::vector<int> v = {1, 2, 3, 4, 3, 5, 3};
    std::cout << "\nДо remove:  "; print(v);

    v.erase(std::remove(v.begin(), v.end(), 3), v.end());
    std::cout << "После:      "; print(v);

    // erase_if (C++20)
    std::vector<int> w = {1, 2, 3, 4, 5, 6};
    std::erase_if(w, [](int x) { return x % 2 == 0; });
    std::cout << "erase_if чёт.: "; print(w);

    return 0;
}