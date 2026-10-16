#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>

// Полиморфные контейнеры: vector<unique_ptr<Base>>.

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

class Rect : public Shape {
    double w_, h_;
public:
    Rect(double w, double h) : w_(w), h_(h) {}
    double area() const override { return w_ * h_; }
    std::string name() const override { return "Прямоугольник"; }
};

int main() {
    std::vector<std::unique_ptr<Shape>> shapes;

    shapes.push_back(std::make_unique<Circle>(5));
    shapes.push_back(std::make_unique<Square>(4));
    shapes.push_back(std::make_unique<Rect>(3, 7));
    shapes.push_back(std::make_unique<Circle>(2));

    std::cout << "=== Все фигуры ===\n";
    double total = 0;
    for (const auto& s : shapes) {
        std::cout << "  " << s->name() << ": " << s->area() << "\n";
        total += s->area();
    }
    std::cout << "Суммарная площадь: " << total << "\n\n";

    // Сортировка по площади — через лямбду, потому что unique_ptr не копируется
    std::sort(shapes.begin(), shapes.end(),
              [](const auto& a, const auto& b) {
                  return a->area() < b->area();
              });

    std::cout << "=== Отсортировано по площади ===\n";
    for (const auto& s : shapes) {
        std::cout << "  " << s->name() << ": " << s->area() << "\n";
    }

    // Максимум
    auto it = std::max_element(shapes.begin(), shapes.end(),
                               [](const auto& a, const auto& b) {
                                   return a->area() < b->area();
                               });
    std::cout << "\nМаксимум: " << (*it)->name()
              << " (" << (*it)->area() << ")\n";

    return 0;
}