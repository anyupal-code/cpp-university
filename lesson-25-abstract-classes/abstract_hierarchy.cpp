#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>

// Иерархия фигур: абстрактный базовый + конкретные наследники.

class Shape {
public:
    virtual ~Shape() = default;

    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual std::string name() const = 0;

    void describe() const {
        std::cout << "  " << name()
                  << ": S = " << area()
                  << ", P = " << perimeter() << "\n";
    }
};

class Circle : public Shape {
    double r_;
public:
    explicit Circle(double r) : r_(r) {}
    double area() const override { return 3.14159 * r_ * r_; }
    double perimeter() const override { return 2 * 3.14159 * r_; }
    std::string name() const override { return "Круг"; }
};

class Rectangle : public Shape {
    double w_, h_;
public:
    Rectangle(double w, double h) : w_(w), h_(h) {}
    double area() const override { return w_ * h_; }
    double perimeter() const override { return 2 * (w_ + h_); }
    std::string name() const override { return "Прямоугольник"; }
};

class Square : public Rectangle {      // Square — частный случай Rectangle
public:
    explicit Square(double s) : Rectangle(s, s) {}
    std::string name() const override { return "Квадрат"; }
};

int main() {
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>(5));
    shapes.push_back(std::make_unique<Rectangle>(3, 4));
    shapes.push_back(std::make_unique<Square>(5));
    shapes.push_back(std::make_unique<Circle>(2));

    std::cout << "=== Все фигуры ===\n";
    double total = 0;
    for (const auto& s : shapes) {
        s->describe();
        total += s->area();
    }
    std::cout << "\nСуммарная площадь: " << total << "\n\n";

    // Сортировка по площади
    std::sort(shapes.begin(), shapes.end(),
              [](const auto& a, const auto& b) {
                  return a->area() < b->area();
              });

    std::cout << "=== По возрастанию площади ===\n";
    for (const auto& s : shapes) {
        s->describe();
    }

    return 0;
}