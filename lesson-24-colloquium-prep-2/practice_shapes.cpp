#include <iostream>
#include <memory>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

// Задача 1. Иерархия фигур.

class Shape {
public:
    virtual ~Shape() = default;

    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual std::string name() const = 0;
};

class Circle : public Shape {
    double r_;
public:
    explicit Circle(double r) : r_(r) {}

    double area() const override { return M_PI * r_ * r_; }
    double perimeter() const override { return 2 * M_PI * r_; }
    std::string name() const override { return "Круг"; }

    double radius() const { return r_; }
};

class Rectangle : public Shape {
    double w_, h_;
public:
    Rectangle(double w, double h) : w_(w), h_(h) {}

    double area() const override { return w_ * h_; }
    double perimeter() const override { return 2 * (w_ + h_); }
    std::string name() const override { return "Прямоугольник"; }

    double width() const { return w_; }
    double height() const { return h_; }
};

class Triangle : public Shape {
    double a_, b_, c_;
public:
    Triangle(double a, double b, double c) : a_(a), b_(b), c_(c) {}

    double area() const override {
        double p = (a_ + b_ + c_) / 2;
        return std::sqrt(p * (p - a_) * (p - b_) * (p - c_));
    }

    double perimeter() const override { return a_ + b_ + c_; }
    std::string name() const override { return "Треугольник"; }
};

void describe(const Shape& s) {
    std::cout << std::setw(16) << std::left << s.name()
              << " S = " << std::setw(8) << std::fixed
              << std::setprecision(2) << s.area()
              << " P = " << s.perimeter() << "\n";
}

int main() {
    std::vector<std::unique_ptr<Shape>> shapes;

    shapes.push_back(std::make_unique<Circle>(5));
    shapes.push_back(std::make_unique<Rectangle>(3, 4));
    shapes.push_back(std::make_unique<Triangle>(3, 4, 5));
    shapes.push_back(std::make_unique<Circle>(2));

    std::cout << "=== Все фигуры ===\n";
    for (const auto& s : shapes) {
        describe(*s);
    }

    // Суммарная площадь
    double total = 0;
    for (const auto& s : shapes) total += s->area();
    std::cout << "\nСуммарная площадь: " << total << "\n\n";

    // Самая большая
    auto max_it = std::max_element(shapes.begin(), shapes.end(),
                                   [](const auto& a, const auto& b) {
                                       return a->area() < b->area();
                                   });
    std::cout << "Самая большая: " << (*max_it)->name()
              << " (" << (*max_it)->area() << ")\n";

    // Сортировка по площади
    std::sort(shapes.begin(), shapes.end(),
              [](const auto& a, const auto& b) {
                  return a->area() < b->area();
              });

    std::cout << "\n=== По возрастанию площади ===\n";
    for (const auto& s : shapes) {
        describe(*s);
    }

    return 0;
}