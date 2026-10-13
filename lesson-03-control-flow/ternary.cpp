#include <iostream>

// Тернарный оператор ?: — краткая форма if-else.

int main() {
    int a = 5, b = 7;

    // Максимум
    int max = (a > b) ? a : b;
    std::cout << "max(" << a << ", " << b << ") = " << max << "\n";

    // Чётность
    int x;
    std::cout << "Введите число: ";
    std::cin >> x;
    std::cout << x << (x % 2 == 0 ? " чётное" : " нечётное") << "\n";

    // Вложенный тернарный — читается плохо, лучше if-else
    int mark = 75;
    std::string grade = (mark >= 90) ? "A"
                      : (mark >= 75) ? "B"
                      : (mark >= 60) ? "C"
                      : "F";
    std::cout << "Оценка: " << grade << "\n";

    return 0;
}
