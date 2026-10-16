#include <iostream>
#include <memory>
#include <vector>

// dynamic_cast в иерархии.

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
    double radius() const { return r_; }
};

class Rectangle : public Shape {
    double w_, h_;
public:
    Rectangle(double w, double h) : w_(w), h_(h) {}
    double area() const override { return w_ * h_; }
    std::string name() const override { return "Прямоугольник"; }
    double width() const { return w_; }
    double height() const { return h_; }
};

int main() {
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>(5));
    shapes.push_back(std::make_unique<Rectangle>(3, 4));
    shapes.push_back(std::make_unique<Circle>(2));
    shapes.push_back(std::make_unique<Rectangle>(5, 5));

    std::cout << "=== Все фигуры ===\n";
    for (const auto& s : shapes) {
        std::cout << s->name() << ": " << s->area() << "\n";

        // Специфично для Circle
        if (auto* c = dynamic_cast<Circle*>(s.get())) {
            std::cout << "  → радиус = " << c->radius() << "\n";
        }

        // Специфично для Rectangle
        if (auto* r = dynamic_cast<Rectangle*>(s.get())) {
            std::cout << "  → стороны = " << r->width()
                      << " x " << r->height() << "\n";
            if (r->width() == r->height()) {
                std::cout << "    (квадрат)\n";
            }
        }
    }

    std::cout << "\n=== Приведение ссылок ===\n";
    Shape* p = shapes[0].get();
    try {
        Circle& c = dynamic_cast<Circle&>(*p);
        std::cout << "  Ссылка на Circle, r = " << c.radius() << "\n";
    } catch (const std::bad_cast&) {
        std::cout << "  не Circle\n";
    }

    Shape* q = shapes[1].get();
    try {
        Circle& c = dynamic_cast<Circle&>(*q);
        std::cout << "  Ссылка на Circle, r = " << c.radius() << "\n";
    } catch (const std::bad_cast&) {
        std::cout << "  не Circle (ожидаемо)\n";
    }

    return 0;
}