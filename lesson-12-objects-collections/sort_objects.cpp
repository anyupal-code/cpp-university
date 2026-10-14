#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// Сортировка объектов: operator<, компаратор, лямбда, несколько критериев.

struct Student {
    std::string name;
    int age;
    double average;

    // Оператор < — по среднему баллу (для std::sort по умолчанию)
    bool operator<(const Student& o) const {
        return average > o.average;   // по убыванию
    }
};

void print(const std::vector<Student>& v) {
    for (const auto& s : v) {
        std::cout << "  " << s.name << ", " << s.age
                  << " лет, средний " << s.average << "\n";
    }
}

int main() {
    std::vector<Student> students = {
        {"Иван",  18, 4.5},
        {"Мария", 19, 4.8},
        {"Пётр",  18, 4.2},
        {"Анна",  20, 4.8},
        {"Олег",  19, 4.5}
    };

    std::cout << "=== Исходный ===\n";
    print(students);

    // 1. По operator< (средний балл, убывание)
    std::sort(students.begin(), students.end());
    std::cout << "\n=== По operator< (средний) ===\n";
    print(students);

    // 2. По имени
    std::sort(students.begin(), students.end(),
              [](const Student& a, const Student& b) {
                  return a.name < b.name;
              });
    std::cout << "\n=== По имени ===\n";
    print(students);

    // 3. По возрасту, при равенстве — по среднему
    std::sort(students.begin(), students.end(),
              [](const Student& a, const Student& b) {
                  if (a.age != b.age) return a.age < b.age;
                  return a.average > b.average;
              });
    std::cout << "\n=== По возрасту, затем по среднему ===\n";
    print(students);

    // 4. Устойчивая сортировка
    std::stable_sort(students.begin(), students.end(),
                     [](const Student& a, const Student& b) {
                         return a.average > b.average;
                     });
    std::cout << "\n=== Устойчиво по среднему ===\n";
    print(students);

    return 0;
}
