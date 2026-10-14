#include <iostream>

// Структуры: объявление, инициализация, доступ к полям.

struct Point {
    int x;
    int y;
};

struct Date {
    int day;
    int month;
    int year;
};

int main() {
    // Инициализация
    Point p1;              // поля не инициализированы
    p1.x = 3;
    p1.y = 5;

    Point p2{1, 2};        // агрегатная инициализация
    Point p3 = {10, 20};

    std::cout << "p1 = (" << p1.x << ", " << p1.y << ")\n";
    std::cout << "p2 = (" << p2.x << ", " << p2.y << ")\n";
    std::cout << "p3 = (" << p3.x << ", " << p3.y << ")\n\n";

    // Изменение
    p1.x = 100;
    std::cout << "p1.x = " << p1.x << "\n\n";

    // Дата
    Date d{14, 10, 2026};
    std::cout << "Дата: "
              << d.day << "."
              << d.month << "."
              << d.year << "\n";

    // Копирование
    Point p4 = p2;
    p4.x = 99;
    std::cout << "\np2 после копии в p4: (" << p2.x << ", " << p2.y << ")\n";
    std::cout << "p4: (" << p4.x << ", " << p4.y << ")\n";

    return 0;
}
