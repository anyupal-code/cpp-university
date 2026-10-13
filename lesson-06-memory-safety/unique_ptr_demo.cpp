#include <iostream>
#include <memory>

// std::unique_ptr — единственный владелец.

struct Point {
    int x, y;

    Point(int x, int y) : x(x), y(y) {
        std::cout << "Point создан\n";
    }

    ~Point() {
        std::cout << "Point уничтожен\n";
    }
};

int main() {
    std::cout << "=== Создание ===\n";
    {
        std::unique_ptr<Point> p = std::make_unique<Point>(1, 2);
        std::cout << "Point: (" << p->x << ", " << p->y << ")\n";
        // p автоматически удалится при выходе из блока
    }
    std::cout << "После блока\n\n";

    std::cout << "=== Перемещение ===\n";
    std::unique_ptr<Point> a = std::make_unique<Point>(3, 4);
    // std::unique_ptr<Point> b = a;   // ошибка: нельзя копировать
    std::unique_ptr<Point> b = std::move(a);   // ок: перемещение
    std::cout << "a == nullptr? " << (a == nullptr) << "\n";
    std::cout << "b: (" << b->x << ", " << b->y << ")\n";

    return 0;
}
