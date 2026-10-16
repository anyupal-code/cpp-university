#include <iostream>
#include <vector>
#include <memory>
#include <string>

// Интерфейс IDrawable + разные фигуры.

class IDrawable {
public:
    virtual ~IDrawable() = default;
    virtual void draw() const = 0;
    virtual std::string type() const = 0;
};

class Circle : public IDrawable {
    double r_;
public:
    explicit Circle(double r) : r_(r) {}

    void draw() const override {
        std::cout << "  ● Круг радиуса " << r_ << "\n";
    }
    std::string type() const override { return "circle"; }
};

class Rectangle : public IDrawable {
    double w_, h_;
public:
    Rectangle(double w, double h) : w_(w), h_(h) {}

    void draw() const override {
        std::cout << "  ▭ Прямоугольник " << w_ << "x" << h_ << "\n";
    }
    std::string type() const override { return "rectangle"; }
};

class Line : public IDrawable {
    double x1_, y1_, x2_, y2_;
public:
    Line(double x1, double y1, double x2, double y2)
        : x1_(x1), y1_(y1), x2_(x2), y2_(y2) {}

    void draw() const override {
        std::cout << "  ／ Линия (" << x1_ << "," << y1_ << ") → ("
                  << x2_ << "," << y2_ << ")\n";
    }
    std::string type() const override { return "line"; }
};

void draw_all(const std::vector<std::unique_ptr<IDrawable>>& items) {
    for (const auto& item : items) {
        item->draw();
    }
}

int main() {
    std::vector<std::unique_ptr<IDrawable>> canvas;
    canvas.push_back(std::make_unique<Circle>(5));
    canvas.push_back(std::make_unique<Rectangle>(3, 4));
    canvas.push_back(std::make_unique<Line>(0, 0, 10, 10));
    canvas.push_back(std::make_unique<Circle>(2));

    std::cout << "=== Рисуем ===\n";
    draw_all(canvas);

    std::cout << "\n=== Типы ===\n";
    for (const auto& item : canvas) {
        std::cout << "  " << item->type() << "\n";
    }

    return 0;
}