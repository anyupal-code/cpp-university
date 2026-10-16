#include <iostream>
#include <memory>
#include <vector>

// dynamic_cast: безопасное приведение вниз.

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
    double radius() const { return r_; }    // специфично для Circle
};

class Square : public Shape {
    double s_;
public:
    explicit Square(double s) : s_(s) {}
    double area() const override { return s_ * s_; }
    std::string name() const override { return "Квадрат"; }
    double side() const { return s_; }      // специфично для Square
};

int main() {
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>(5));
    shapes.push_back(std::make_unique<Square>(4));
    shapes.push_back(std::make_unique<Circle>(2));

    for (const auto& s : shapes) {
        std::cout << s->name() << ": площадь " << s->area() << "\n";

        // Попытка привести к Circle
        if (auto* c = dynamic_cast<Circle*>(s.get())) {
            std::cout << "  → это круг, радиус = " << c->radius() << "\n";
        }

        // Попытка привести к Square
        if (auto* sq = dynamic_cast<Square*>(s.get())) {
            std::cout << "  → это квадрат, сторона = " << sq->side() << "\n";
        }
    }

    // Неудачное приведение
    std::cout << "\n=== Неудачное приведение ===\n";
    Shape* base = new Circle(3);

    Square* s = dynamic_cast<Square*>(base);
    std::cout << "Circle* -> Square*: " << (s == nullptr ? "nullptr" : "ok") << "\n";

    Circle* c = dynamic_cast<Circle*>(base);
    std::cout << "Circle* -> Circle*: " << (c == nullptr ? "nullptr" : "ok") << "\n";

    delete base;

    return 0;
}