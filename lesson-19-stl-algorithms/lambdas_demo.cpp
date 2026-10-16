#include <iostream>
#include <vector>
#include <algorithm>

// Лямбды: захваты, mutable, generic.

int main() {
    std::cout << "=== Простая лямбда ===\n";
    auto square = [](int x) { return x * x; };
    std::cout << "square(5) = " << square(5) << "\n";

    auto add = [](int a, int b) { return a + b; };
    std::cout << "add(3, 7) = " << add(3, 7) << "\n\n";

    std::cout << "=== Захват по значению ===\n";
    int base = 100;
    auto add_base = [base](int x) { return x + base; };
    std::cout << "add_base(5) = " << add_base(5) << "\n";
    base = 200;
    std::cout << "После base = 200: add_base(5) = " << add_base(5)
              << " (захвачено старое значение)\n\n";

    std::cout << "=== Захват по ссылке ===\n";
    int counter = 0;
    auto inc = [&counter]() { ++counter; };
    inc();
    inc();
    inc();
    std::cout << "counter = " << counter << "\n\n";

    std::cout << "=== mutable ===\n";
    int captured = 0;
    auto mut = [captured]() mutable { return ++captured; };
    std::cout << "mut() = " << mut() << "\n";
    std::cout << "mut() = " << mut() << "\n";
    std::cout << "mut() = " << mut() << "\n";
    std::cout << "Внешний captured = " << captured
              << " (не изменился)\n\n";

    std::cout << "=== Захват всех ===\n";
    int a = 1, b = 2, c = 3;

    auto sum_by_value = [=]() { return a + b + c; };
    auto sum_by_ref = [&]() { return a + b + c; };

    std::cout << "sum_by_value() = " << sum_by_value() << "\n";

    a = 100;
    std::cout << "После a = 100:\n";
    std::cout << "  sum_by_value() = " << sum_by_value() << " (старые)\n";
    std::cout << "  sum_by_ref()   = " << sum_by_ref() << " (новые)\n\n";

    std::cout << "=== Generic-лямбда (C++14) ===\n";
    auto print = [](const auto& x) {
        std::cout << "  " << x << "\n";
    };
    print(42);
    print("hello");
    print(3.14);

    std::cout << "\n=== Лямбда в алгоритме ===\n";
    std::vector<int> v = {5, 2, 8, 1, 9, 3};
    std::sort(v.begin(), v.end(),
              [](int x, int y) { return x > y; });
    std::cout << "По убыванию: ";
    for (int x : v) std::cout << x << " ";
    std::cout << "\n";

    return 0;
}