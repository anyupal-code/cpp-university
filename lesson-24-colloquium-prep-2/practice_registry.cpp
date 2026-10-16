#include <iostream>
#include <memory>
#include <unordered_map>
#include <string>
#include <vector>

// Задача 3. Реестр фигур.

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

class ShapeRegistry {
private:
    std::unordered_map<std::string, std::unique_ptr<Shape>> items_;

public:
    void add(const std::string& key, std::unique_ptr<Shape> shape) {
        items_[key] = std::move(shape);
    }

    Shape* get(const std::string& key) {
        auto it = items_.find(key);
        return (it != items_.end()) ? it->second.get() : nullptr;
    }

    bool remove(const std::string& key) {
        return items_.erase(key) > 0;
    }

    std::size_t size() const { return items_.size(); }

    std::vector<std::string> keys() const {
        std::vector<std::string> result;
        result.reserve(items_.size());
        for (const auto& [k, v] : items_) result.push_back(k);
        return result;
    }

    void print_all() const {
        for (const auto& [key, shape] : items_) {
            std::cout << "  " << key << ": " << shape->name()
                      << " (S = " << shape->area() << ")\n";
        }
    }
};

int main() {
    ShapeRegistry registry;

    std::cout << "=== Добавление ===\n";
    registry.add("circle1", std::make_unique<Circle>(5));
    registry.add("square1", std::make_unique<Square>(4));
    registry.add("circle2", std::make_unique<Circle>(2));
    registry.add("square2", std::make_unique<Square>(3));

    std::cout << "Размер реестра: " << registry.size() << "\n\n";

    std::cout << "=== Содержимое ===\n";
    registry.print_all();

    std::cout << "\n=== get ===\n";
    if (auto* s = registry.get("circle1")) {
        std::cout << "circle1: " << s->name() << " (S = " << s->area() << ")\n";
    }

    if (auto* s = registry.get("missing")) {
        std::cout << "найдено\n";
    } else {
        std::cout << "missing: nullptr\n";
    }

    std::cout << "\n=== remove ===\n";
    std::cout << "remove square1: " << registry.remove("square1") << "\n";
    std::cout << "remove unknown: " << registry.remove("unknown") << "\n";
    std::cout << "Размер: " << registry.size() << "\n\n";

    std::cout << "=== Все ключи ===\n";
    for (const auto& k : registry.keys()) {
        std::cout << "  " << k << "\n";
    }

    return 0;
}