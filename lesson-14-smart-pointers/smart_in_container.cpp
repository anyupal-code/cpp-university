#include <iostream>
#include <memory>
#include <vector>

// Умные указатели в контейнерах.

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

int main() {
    std::cout << "=== vector<unique_ptr<Shape>> ===\n";
    std::vector<std::unique_ptr<Shape>> v;
    v.push_back(std::make_unique<Circle>(5));
    v.push_back(std::make_unique<Square>(4));
    v.push_back(std::make_unique<Circle>(2));

    for (const auto& s : v) {
        std::cout << "  " << s->name() << ": " << s->area() << "\n";
    }

    // Можно переместить из контейнера
    std::cout << "\n=== Перемещение из контейнера ===\n";
    auto taken = std::move(v[0]);
    std::cout << "  Взяли: " << taken->name() << "\n";
    std::cout << "  v[0] == nullptr? " << (v[0] == nullptr) << "\n\n";

    // shared_ptr в контейнере
    std::cout << "=== vector<shared_ptr<Shape>> ===\n";
    std::vector<std::shared_ptr<Shape>> shared;
    auto c = std::make_shared<Circle>(3);
    shared.push_back(c);
    shared.push_back(c);   // один объект — два слота
    shared.push_back(std::make_shared<Square>(2));

    std::cout << "c.use_count() = " << c.use_count() << "\n";

    for (const auto& s : shared) {
        std::cout << "  " << s->name() << ": " << s->area() << "\n";
    }

    return 0;
}
