#include <iostream>

// switch: case, default, fall-through.

int main() {
    int day;
    std::cout << "День недели (1-7): ";
    std::cin >> day;

    switch (day) {
        case 1:
            std::cout << "Понедельник\n";
            break;
        case 2:
            std::cout << "Вторник\n";
            break;
        case 3:
            std::cout << "Среда\n";
            break;
        case 4:
            std::cout << "Четверг\n";
            break;
        case 5:
            std::cout << "Пятница\n";
            break;
        case 6:
        case 7:
            std::cout << "Выходной\n";
            break;
        default:
            std::cout << "Неверный номер\n";
    }

    // Намеренный fall-through (C++17)
    char grade;
    std::cout << "\nОценка (A-E): ";
    std::cin >> grade;

    switch (grade) {
        case 'A':
            std::cout << "Отлично! ";
            [[fallthrough]];
        case 'B':
            std::cout << "Хорошо! ";
            [[fallthrough]];
        case 'C':
            std::cout << "Удовлетворительно\n";
            break;
        case 'D':
        case 'E':
            std::cout << "Плохо\n";
            break;
        default:
            std::cout << "Неизвестная оценка\n";
    }

    return 0;
}