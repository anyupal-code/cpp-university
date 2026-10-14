#include <iostream>
#include <vector>
#include <string>

// Массив структур и vector структур.

struct Student {
    std::string name;
    int age;
    double average;
};

int main() {
    // Статический массив
    Student group[3] = {
        {"Иван", 18, 4.5},
        {"Мария", 19, 4.8},
        {"Пётр", 18, 4.2}
    };

    std::cout << "=== Статический массив ===\n";
    for (const auto& s : group) {
        std::cout << s.name << ", " << s.age
                  << " лет, средний " << s.average << "\n";
    }

    // vector
    std::vector<Student> v;
    v.push_back({"Анна", 20, 4.9});
    v.push_back({"Олег", 18, 4.0});

    std::cout << "\n=== vector ===\n";
    for (const auto& s : v) {
        std::cout << s.name << ", " << s.age
                  << " лет, средний " << s.average << "\n";
    }

    // Средний балл группы
    double sum = 0;
    for (const auto& s : v) sum += s.average;
    std::cout << "\nСредний балл vector: " << sum / v.size() << "\n";

    return 0;
}
