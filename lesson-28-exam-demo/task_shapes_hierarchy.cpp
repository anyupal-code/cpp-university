#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>

// Задача 3. Иерархия фигур с полиморфизмом и clone().

class Shape {
public:
    virtual ~Shape() = default;

    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual std::string name() const = 0;
    virtual std::unique_ptr<Shape> clone() const = 0;   // ← Prototype
};

class Circle : public Shape {
    double r_;
public:
    explicit Circle(double r) : r_(r) {}
    double area() const override { return M_PI * r_ * r_; }
    double perimeter() const override { return 2 * M_PI * r_; }
    std::string name() const override { return "Круг"; }

    std::unique_ptr<Shape> clone() const override {
        return std::make_unique<Circle>(*this);
    }
};

class Rectangle : public Shape {
    double w_, h_;
public:
    Rectangle(double w, double h) : w_(w), h_(h) {}
    double area() const override { return w_ * h_; }
    double perimeter() const override { return 2 * (w_ + h_); }
    std::string name() const override { return "Прямоугольник"; }

    std::unique_ptr<Shape> clone() const override {
        return std::make_unique<Rectangle>(*this);
    }
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

    std::unique_ptr<Shape> clone() const override {
        return std::make_unique<Triangle>(*this);
    }
};

std::ostream& operator<<(std::ostream& os, const Shape& s) {
    os << std::setw(16) << std::left << s.name()
       << " S = " << std::setw(8) << std::fixed << std::setprecision(2) << s.area()
       << " P = " << s.perimeter();
    return os;
}

void analyze(const std::vector<std::unique_ptr<Shape>>& shapes) {
    double total = 0;
    const Shape* max_shape = nullptr;

    for (const auto& s : shapes) {
        total += s->area();
        if (!max_shape || s->area() > max_shape->area()) {
            max_shape = s.get();
        }
    }

    std::cout << "Всего фигур:  " << shapes.size() << "\n";
    std::cout << "Суммарно S:   " << total << "\n";
    std::cout << "Максимум:     " << max_shape->name()
              << " (" << max_shape->area() << ")\n";
}

int main() {
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>(5));
    shapes.push_back(std::make_unique<Rectangle>(3, 4));
    shapes.push_back(std::make_unique<Triangle>(3, 4, 5));
    shapes.push_back(std::make_unique<Circle>(2));
    shapes.push_back(std::make_unique<Rectangle>(5, 5));

    std::cout << "=== Все фигуры ===\n";
    for (const auto& s : shapes) {
        std::cout << *s << "\n";
    }

    std::cout << "\n=== Анализ ===\n";
    analyze(shapes);

    // Сортировка по площади
    std::sort(shapes.begin(), shapes.end(),
              [](const auto& a, const auto& b) {
                  return a->area() < b->area();
              });

    std::cout << "\n=== По возрастанию площади ===\n";
    for (const auto& s : shapes) {
        std::cout << *s << "\n";
    }

    // Клонирование (Prototype)
    std::cout << "\n=== Клонирование через clone() ===\n";
    std::vector<std::unique_ptr<Shape>> clones;
    for (const auto& s : shapes) {
        clones.push_back(s->clone());   // глубокое копирование
    }

    std::cout << "Оригиналов: " << shapes.size()
              << ", клонов: " << clones.size() << "\n";

    // Проверка: изменения в клоне не влияют на оригинал
    clones[0] = std::make_unique<Circle>(100);
    std::cout << "После замены clones[0] размер остался: "
              << clones.size() << "\n";

    return 0;
}