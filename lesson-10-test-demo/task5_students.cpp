#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

// Задача 5. Студенты.
// Сортировка по среднему баллу (убыв.), при равенстве — по имени (возр.).

struct Student {
    std::string name;
    int age;
    double average;
};

int main() {
    std::vector<Student> students = {
        {"Иван",   18, 4.5},
        {"Мария",  19, 4.8},
        {"Пётр",   18, 4.2},
        {"Анна",   20, 4.8},
        {"Олег",   19, 4.5},
        {"Елена",  18, 4.9}
    };

    std::sort(students.begin(), students.end(),
              [](const Student& a, const Student& b) {
                  if (a.average != b.average)
                      return a.average > b.average;   // больше — выше
                  return a.name < b.name;              // по имени
              });

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "=== Отсортированные студенты ===\n";
    for (const auto& s : students) {
        std::cout << std::setw(8) << std::left << s.name
                  << " возраст: " << s.age
                  << ", средний: " << s.average << "\n";
    }

    // Средний балл группы
    double sum = 0;
    for (const auto& s : students) sum += s.average;
    std::cout << "\nСредний балл группы: " << sum / students.size() << "\n";

    // Топ-3
    std::cout << "\nТоп-3:\n";
    for (int i = 0; i < 3 && i < static_cast<int>(students.size()); ++i) {
        std::cout << "  " << (i + 1) << ". " << students[i].name
                  << " (" << students[i].average << ")\n";
    }

    return 0;
}
