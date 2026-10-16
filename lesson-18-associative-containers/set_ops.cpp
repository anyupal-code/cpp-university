#include <iostream>
#include <set>
#include <algorithm>
#include <iterator>

// Операции над множествами: объединение, пересечение, разность.

template <typename T>
void print(const std::set<T>& s) {
    std::cout << "{";
    bool first = true;
    for (const auto& x : s) {
        if (!first) std::cout << ", ";
        std::cout << x;
        first = false;
    }
    std::cout << "}";
}

int main() {
    std::set<int> a = {1, 2, 3, 4, 5};
    std::set<int> b = {4, 5, 6, 7};

    std::cout << "a = "; print(a); std::cout << "\n";
    std::cout << "b = "; print(b); std::cout << "\n\n";

    // Объединение
    std::set<int> uni;
    std::set_union(a.begin(), a.end(),
                   b.begin(), b.end(),
                   std::inserter(uni, uni.begin()));
    std::cout << "a ∪ b = "; print(uni); std::cout << "\n";

    // Пересечение
    std::set<int> inter;
    std::set_intersection(a.begin(), a.end(),
                          b.begin(), b.end(),
                          std::inserter(inter, inter.begin()));
    std::cout << "a ∩ b = "; print(inter); std::cout << "\n";

    // Разность a - b
    std::set<int> diff;
    std::set_difference(a.begin(), a.end(),
                        b.begin(), b.end(),
                        std::inserter(diff, diff.begin()));
    std::cout << "a − b = "; print(diff); std::cout << "\n";

    // Симметрическая разность
    std::set<int> sym;
    std::set_symmetric_difference(a.begin(), a.end(),
                                  b.begin(), b.end(),
                                  std::inserter(sym, sym.begin()));
    std::cout << "a △ b = "; print(sym); std::cout << "\n";

    // Проверка подмножества
    std::set<int> c = {1, 2};
    std::cout << "\n{1, 2} ⊆ a? "
              << std::includes(a.begin(), a.end(),
                               c.begin(), c.end()) << "\n";

    return 0;
}