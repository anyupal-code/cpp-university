#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ranges>
#include <tuple>
#include <iomanip>

// Задача 3. Многокритериальная сортировка студентов.
// 1. Средний балл — по убыванию.
// 2. Возраст — по возрастанию.
// 3. Имя — по возрастанию.

struct Student {
    std::string name;
    int age;
    double average;
};

void print(const std::vector<Student>& v) {
    for (const auto& s : v) {
        std::cout << "  " << std::setw(8) << std::left << s.name
                  << " возраст: " << s.age
                  << ", средний: " << s.average << "\n";
    }
}

int main() {
    std::vector<Student> students = {
        {"Иван",   18, 4.5},
        {"Мария",  19, 4.8},
        {"Пётр",   18, 4.5},
        {"Анна",   20, 4.8},
        {"Олег",   18, 4.8},
        {"Елена",  19, 4.5},
        {"Сергей", 20, 4.5}
    };

    std::cout << "=== Исходный ===\n";
    print(students);

    // Способ 1: лямбда с каскадом
    std::cout << "\n=== Способ 1 (лямбда) ===\n";
    auto v1 = students;
    std::sort(v1.begin(), v1.end(),
              [](const Student& a, const Student& b) {
                  if (a.average != b.average) return a.average > b.average;
                  if (a.age != b.age) return a.age < b.age;
                  return a.name < b.name;
              });
    print(v1);

    // Способ 2 (C++20): кортеж + проекция
    std::cout << "\n=== Способ 2 (ranges + tuple) ===\n";
    auto v2 = students;
    std::ranges::sort(v2, std::less{}, [](const Student& s) {
        return std::tuple{-s.average, s.age, s.name};
    });
    print(v2);

    // Топ-3
    std::cout << "\n=== Топ-3 ===\n";
    std::ranges::partial_sort(v2, v2.begin() + 3, std::less{},
                              [](const Student& s) {
                                  return std::tuple{-s.average, s.age, s.name};
                              });
    for (int i = 0; i < 3; ++i) {
        std::cout << "  " << (i + 1) << ". " << v2[i].name
                  << " (" << v2[i].average << ")\n";
    }

    return 0;
}