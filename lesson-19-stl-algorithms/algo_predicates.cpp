#include <iostream>
#include <vector>
#include <algorithm>

// Предикаты: find_if, count_if, remove_if, partition.

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
    std::vector<int> v = {15, 3, 22, 8, 41, 7, 60, 12};
    std::cout << "v = "; print(v);
    std::cout << "\n";

    // find_if: первый > 20
    auto it = std::find_if(v.begin(), v.end(),
                           [](int x) { return x > 20; });
    if (it != v.end()) {
        std::cout << "Первый > 20: " << *it
                  << " (позиция " << (it - v.begin()) << ")\n";
    }

    // find_if_not: первый не делящийся на 3
    auto it2 = std::find_if_not(v.begin(), v.end(),
                                [](int x) { return x % 3 == 0; });
    if (it2 != v.end()) {
        std::cout << "Первый не кратный 3: " << *it2 << "\n";
    }
    std::cout << "\n";

    // count_if
    int count_even = std::count_if(v.begin(), v.end(),
                                   [](int x) { return x % 2 == 0; });
    std::cout << "Чётных: " << count_even << "\n\n";

    // remove_if — «сдвигает» элементы, требует erase
    std::vector<int> w = v;
    std::cout << "До remove_if(> 20): "; print(w);

    auto new_end = std::remove_if(w.begin(), w.end(),
                                  [](int x) { return x > 20; });
    std::cout << "После remove_if:    "; print(w);
    std::cout << "  (реальный размер не изменился)\n";

    w.erase(new_end, w.end());
    std::cout << "После erase:        "; print(w);

    // partition: разделить по предикату
    std::vector<int> p = {1, 2, 3, 4, 5, 6, 7, 8};
    auto pivot = std::partition(p.begin(), p.end(),
                                [](int x) { return x % 2 == 0; });
    std::cout << "\npartition чётные → начало:\n";
    std::cout << "  "; print(p);
    std::cout << "  pivot на позиции " << (pivot - p.begin()) << "\n";

    // is_partitioned
    std::cout << "is_partitioned? "
              << std::is_partitioned(p.begin(), p.end(),
                                     [](int x) { return x % 2 == 0; }) << "\n";

    return 0;
}