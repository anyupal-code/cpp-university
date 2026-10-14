#include <iostream>
#include <memory>
#include <vector>

// unique_ptr с полиморфизмом: базовый класс + наследники.

class Shape {
public:
    virtual ~Shape() = default;    // ОБЯЗАТЕЛЬНО виртуальный деструктор
    virtual double area() const = 0;
    virtual std::string name() const = 0;
};

class Circle : public Shape {
private:
    double r_;
public:
    explicit Circle(double r) : r_(r) {}
    double area() const override { return 3.14159 * r_ * r_; }
    std::string name() const override { return "Круг"; }
};

class Rect : public Shape {
private:
    double w_, h_;
public:
    Rect(double w, double h) : w_(w), h_(h) {}
    double area() const override { return w_ * h_; }
    std::string name() const override { return "Прямоугольник"; }
};

int main() {
    std::vector<std::unique_ptr<Shape>> shapes;

    shapes.push_back(std::make_unique<Circle>(5));
    shapes.push_back(std::make_unique<Rect>(3, 4));
    shapes.push_back(std::make_unique<Circle>(1));

    double total = 0;
    for (const auto& s : shapes) {
        std::cout << s->name() << ": " << s->area() << "\n";
        total += s->area();
    }
    std::cout << "Суммарная площадь: " << total << "\n";

    // Все объекты уничтожатся автоматически
    // через виртуальный деструктор

    return 0;
}
