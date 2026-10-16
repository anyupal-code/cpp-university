#include <iostream>

// Простой абстрактный класс.

class Shape {
public:
    virtual ~Shape() = default;

    virtual double area() const = 0;      // чистая виртуальная

    virtual std::string name() const = 0;
};

class Circle : public Shape {
    double r_;
public:
    explicit Circle(double r) : r_(r) {}

    double area() const override { return 3.14159 * r_ * r_; }
    std::string name() const override { return "Круг"; }
};

class Square : public Shape {
    double s_;
public:
    explicit Square(double s) : s_(s) {}

    double area() const override { return s_ * s_; }
    std::string name() const override { return "Квадрат"; }
};

int main() {
    // Shape s;              // ошибка компиляции
    // Shape* p = new Shape; // тоже ошибка

    // Shape* p = new Circle(5);   // ок — через указатель
    // Circle c(3);                // ок — конкретный класс

    Circle c(5);
    Square s(4);

    std::cout << c.name() << ": " << c.area() << "\n";
    std::cout << s.name() << ": " << s.area() << "\n";

    // Полиморфизм
    Shape* ptr = &c;
    std::cout << "\nЧерез Shape*: " << ptr->name()
              << " S = " << ptr->area() << "\n";

    ptr = &s;
    std::cout << "Через Shape*: " << ptr->name()
              << " S = " << ptr->area() << "\n";

    // Срезка — ошибка компиляции
    // Shape sliced = c;   // нельзя

    return 0;
}