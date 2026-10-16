#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>

// Обзор: virtual, override, final, полиморфизм.

class Shape {
public:
    virtual ~Shape() = default;
    virtual double area() const = 0;
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

// final: от этого класса нельзя наследовать
class Triangle final : public Shape {
    double a_, b_, c_;
public:
    Triangle(double a, double b, double c) : a_(a), b_(b), c_(c) {}

    double area() const override {
        double p = (a_ + b_ + c_) / 2;
        return std::sqrt(p * (p - a_) * (p - b_) * (p - c_));
    }

    std::string name() const override { return "Треугольник"; }
};

int main() {
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>(5));
    shapes.push_back(std::make_unique<Square>(4));
    shapes.push_back(std::make_unique<Triangle>(3, 4, 5));

    std::cout << "=== Все фигуры ===\n";
    double total = 0;
    for (const auto& s : shapes) {
        std::cout << "  " << s->name() << ": " << s->area() << "\n";
        total += s->area();
    }
    std::cout << "Суммарно: " << total << "\n\n";

    // Сортировка
    std::sort(shapes.begin(), shapes.end(),
              [](const auto& a, const auto& b) {
                  return a->area() < b->area();
              });

    std::cout << "=== Отсортировано ===\n";
    for (const auto& s : shapes) {
        std::cout << "  " << s->name() << ": " << s->area() << "\n";
    }

    return 0;
}