#include <iostream>
#include <cmath>

// Методы внутри структуры. const-методы.

struct Point {
    double x = 0;
    double y = 0;

    // Конструктор по умолчанию
    Point() = default;

    // Конструктор с параметрами
    Point(double x, double y) : x(x), y(y) {}

    // const-метод: не меняет объект
    void print() const {
        std::cout << "(" << x << ", " << y << ")\n";
    }

    double length() const {
        return std::sqrt(x * x + y * y);
    }

    // Не const — меняет объект
    void move(double dx, double dy) {
        x += dx;
        y += dy;
    }

    void scale(double k) {
        x *= k;
        y *= k;
    }
};

// Функция принимает константную ссылку
void print_twice(const Point& p) {
    p.print();
    p.print();   // ok, потому что print() const
}

int main() {
    Point a{3, 4};

    std::cout << "a = "; a.print();
    std::cout << "Длина: " << a.length() << "\n";

    a.move(1, 1);
    std::cout << "После move: "; a.print();

    a.scale(2);
    std::cout << "После scale(2): "; a.print();

    std::cout << "\nКонстантный объект:\n";
    const Point b{5, 12};
    b.print();                    // ok — print() const
    std::cout << "Длина: " << b.length() << "\n";
    // b.move(1, 1);              // ошибка: move() не const

    std::cout << "\nprint_twice:\n";
    print_twice(a);

    return 0;
}
