#include <iostream>
#include <memory>
#include <vector>
#include <string>

// Абстрактная фабрика: создание объектов без знания конкретных типов.

class Shape {
public:
    virtual ~Shape() = default;
    virtual double area() const = 0;
    virtual std::string name() const = 0;

    void print() const {
        std::cout << "  " << name() << ": " << area() << "\n";
    }
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

class Triangle : public Shape {
    double a_, h_;
public:
    Triangle(double a, double h) : a_(a), h_(h) {}
    double area() const override { return 0.5 * a_ * h_; }
    std::string name() const override { return "Треугольник"; }
};

// Фабрика
class ShapeFactory {
public:
    enum Type { CircleT, SquareT, TriangleT };

    static std::unique_ptr<Shape> create(Type type, double a, double b = 0) {
        switch (type) {
            case CircleT:   return std::make_unique<Circle>(a);
            case SquareT:   return std::make_unique<Square>(a);
            case TriangleT: return std::make_unique<Triangle>(a, b);
        }
        return nullptr;
    }

    static std::unique_ptr<Shape> create_by_name(const std::string& name,
                                                  double a, double b = 0) {
        if (name == "circle")   return std::make_unique<Circle>(a);
        if (name == "square")   return std::make_unique<Square>(a);
        if (name == "triangle") return std::make_unique<Triangle>(a, b);
        return nullptr;
    }
};

int main() {
    std::cout << "=== Через enum ===\n";
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(ShapeFactory::create(ShapeFactory::CircleT, 5));
    shapes.push_back(ShapeFactory::create(ShapeFactory::SquareT, 4));
    shapes.push_back(ShapeFactory::create(ShapeFactory::TriangleT, 6, 3));

    for (const auto& s : shapes) {
        s->print();
    }

    std::cout << "\n=== Через имя ===\n";
    auto c = ShapeFactory::create_by_name("circle", 3);
    auto s = ShapeFactory::create_by_name("square", 5);
    auto t = ShapeFactory::create_by_name("triangle", 4, 2);

    c->print();
    s->print();
    t->print();

    return 0;
}