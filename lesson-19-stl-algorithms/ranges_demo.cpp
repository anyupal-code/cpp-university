#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>
#include <string>

// ranges и views (C++20).

// Принимаем по обычной ссылке — filter/transform не дают const begin()
template <typename Range>
void print_range(Range& r) {
    std::cout << "[";
    bool first = true;
    for (const auto& x : r) {
        if (!first) std::cout << ", ";
        std::cout << x;
        first = false;
    }
    std::cout << "]\n";
}

int main() {
    std::vector<int> v = {5, 2, 8, 1, 9, 3, 7, 4, 6, 10};

    std::cout << "v = "; print_range(v);
    std::cout << "\n";

    // ranges::sort без begin/end
    auto s = v;
    std::ranges::sort(s);
    std::cout << "ranges::sort:      "; print_range(s);

    // ranges::find
    auto it = std::ranges::find(v, 8);
    std::cout << "ranges::find(8):   "
              << (it != v.end() ? "найдено" : "нет") << "\n\n";

    // filter
    std::cout << "=== views::filter ===\n";
    auto evens = v | std::views::filter([](int x) { return x % 2 == 0; });
    std::cout << "Чётные:            "; print_range(evens);

    // transform
    auto squares = v | std::views::transform([](int x) { return x * x; });
    std::cout << "Квадраты:          "; print_range(squares);
    std::cout << "\n";

    // Комбинация: filter + transform + take
    std::cout << "=== Комбинация ===\n";
    auto result = v
        | std::views::filter([](int x) { return x % 2 == 0; })
        | std::views::transform([](int x) { return x * 10; })
        | std::views::take(3);

    std::cout << "Чётные × 10, первые 3: "; print_range(result);
    std::cout << "\n";

    // reverse
    std::cout << "reverse:           ";
    for (int x : v | std::views::reverse) std::cout << x << " ";
    std::cout << "\n";

    // drop
    std::cout << "drop(5):           ";
    for (int x : v | std::views::drop(5)) std::cout << x << " ";
    std::cout << "\n\n";

    // ranges::sort с проекцией
    struct Student {
        std::string name;
        double avg;
    };

    std::vector<Student> students = {
        {"Иван",  4.5},
        {"Мария", 4.8},
        {"Пётр",  4.2}
    };

    std::ranges::sort(students, {}, &Student::avg);

    std::cout << "=== Сортировка по avg через проекцию ===\n";
    for (const auto& s : students) {
        std::cout << "  " << s.name << ": " << s.avg << "\n";
    }

    return 0;
}
