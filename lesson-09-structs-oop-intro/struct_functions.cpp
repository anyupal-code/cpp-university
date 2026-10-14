#include <iostream>
#include <cmath>

// Структура как параметр функции: по значению и по ссылке.

struct Point {
    double x = 0;
    double y = 0;
};

// По константной ссылке — не копирует, не меняет
void print(const Point& p) {
    std::cout << "(" << p.x << ", " << p.y << ")\n";
}

// По ссылке — меняет оригинал
void move(Point& p, double dx, double dy) {
    p.x += dx;
    p.y += dy;
}

// Возврат структуры
Point make_point(double x, double y) {
    return {x, y};
}

// Расстояние между точками
double distance(const Point& a, const Point& b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return std::sqrt(dx * dx + dy * dy);
}

int main() {
    Point a{0, 0};
    Point b{3, 4};

    std::cout << "a = "; print(a);
    std::cout << "b = "; print(b);

    std::cout << "\nРасстояние: " << distance(a, b) << "\n";

    move(a, 1, 1);
    std::cout << "\nПосле move(a, 1, 1): a = "; print(a);

    Point c = make_point(10, 20);
    std::cout << "c = "; print(c);

    return 0;
}
