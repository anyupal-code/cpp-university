#include <iostream>
#include <typeinfo>
#include <memory>
#include <vector>

// RTTI: typeid.

class Shape {
public:
    virtual ~Shape() = default;
};

class Circle : public Shape {};
class Square : public Shape {};
class Triangle : public Shape {};

int main() {
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>());
    shapes.push_back(std::make_unique<Square>());
    shapes.push_back(std::make_unique<Triangle>());
    shapes.push_back(std::make_unique<Circle>());

    std::cout << "=== typeid(*p).name() ===\n";
    for (const auto& s : shapes) {
        std::cout << "  " << typeid(*s).name() << "\n";
    }

    // Сравнение типов
    std::cout << "\n=== Сравнение ===\n";
    Shape* p = shapes[0].get();

    std::cout << "typeid(*p) == typeid(Circle)? "
              << (typeid(*p) == typeid(Circle)) << "\n";
    std::cout << "typeid(*p) == typeid(Square)? "
              << (typeid(*p) == typeid(Square)) << "\n";

    // Хеш-код типа
    std::cout << "\nhash_code: " << typeid(*p).hash_code() << "\n";

    // Подсчёт по типам
    std::cout << "\n=== Подсчёт по типам ===\n";
    int circles = 0, squares = 0, triangles = 0;
    for (const auto& s : shapes) {
        if (typeid(*s) == typeid(Circle)) ++circles;
        else if (typeid(*s) == typeid(Square)) ++squares;
        else if (typeid(*s) == typeid(Triangle)) ++triangles;
    }
    std::cout << "Кругов:    " << circles << "\n";
    std::cout << "Квадратов: " << squares << "\n";
    std::cout << "Треуг.:    " << triangles << "\n";

    std::cout << "\nПримечание: имена искажены (mangling).\n";
    std::cout << "Для читаемых имён — abi::__cxa_demangle (Linux) или boost::typeindex.\n";

    return 0;
}