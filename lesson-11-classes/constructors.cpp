#include <iostream>

// Конструкторы: по умолчанию, с параметрами, делегирующий, explicit.

class Point {
private:
    int x_;
    int y_;

public:
    // Конструктор по умолчанию
    Point() : Point(0, 0) {
        std::cout << "  [Point()]\n";
    }

    // Основной конструктор
    Point(int x, int y) : x_(x), y_(y) {
        std::cout << "  [Point(int, int)]\n";
    }

    void print() const {
        std::cout << "(" << x_ << ", " << y_ << ")\n";
    }
};

class Meter {
private:
    double value_;

public:
    explicit Meter(double v) : value_(v) {}

    double value() const { return value_; }
};

void print_meter(const Meter& m) {
    std::cout << m.value() << " м\n";
}

int main() {
    std::cout << "Создание Point p1:\n";
    Point p1;
    p1.print();

    std::cout << "\nСоздание Point p2(3, 5):\n";
    Point p2(3, 5);
    p2.print();

    std::cout << "\nСоздание Point p3{1, 2}:\n";
    Point p3{1, 2};
    p3.print();

    std::cout << "\n---\n";
    std::cout << "Meter:\n";
    Meter m(3.14);
    print_meter(m);

    // Meter m2 = 5.0;   // ошибка: explicit
    Meter m2(5.0);       // ок
    print_meter(m2);

    return 0;
}
