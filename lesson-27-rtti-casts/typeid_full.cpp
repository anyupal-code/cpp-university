#include <iostream>
#include <typeinfo>
#include <memory>
#include <vector>
#include <unordered_map>

// RTTI: typeid, type_info.

class Shape {
public:
    virtual ~Shape() = default;
};

class Circle : public Shape {};
class Square : public Shape {};
class Triangle : public Shape {};

template <typename T>
T max_generic(T a, T b) {
    return (a > b) ? a : b;
}

int main() {
    std::cout << "=== typeid для встроенных типов ===\n";
    std::cout << "  int:     " << typeid(int).name() << "\n";
    std::cout << "  double:  " << typeid(double).name() << "\n";
    std::cout << "  char:    " << typeid(char).name() << "\n";

    std::cout << "\n=== typeid для объектов ===\n";
    Circle c;
    Square s;

    std::cout << "  Circle:     " << typeid(c).name() << "\n";
    std::cout << "  Square:     " << typeid(s).name() << "\n";

    std::cout << "\n=== Через базовый указатель ===\n";
    Shape* p = &c;
    std::cout << "  typeid(*p): " << typeid(*p).name()
              << "  (фактический тип)\n";
    std::cout << "  typeid(p):  " << typeid(p).name()
              << "  (тип указателя)\n";

    std::cout << "\n=== Сравнение ===\n";
    std::cout << "  typeid(*p) == typeid(Circle)? "
              << (typeid(*p) == typeid(Circle)) << "\n";
    std::cout << "  typeid(*p) == typeid(Square)? "
              << (typeid(*p) == typeid(Square)) << "\n";
    std::cout << "  typeid(*p) == typeid(Shape)?  "
              << (typeid(*p) == typeid(Shape)) << "\n";
    std::cout << "  (typeid — точное совпадение, не «является ли»)\n";

    std::cout << "\n=== hash_code ===\n";
    std::cout << "  Circle hash: " << typeid(Circle).hash_code() << "\n";
    std::cout << "  Square hash: " << typeid(Square).hash_code() << "\n";

    std::cout << "\n=== Подсчёт по типам ===\n";
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>());
    shapes.push_back(std::make_unique<Square>());
    shapes.push_back(std::make_unique<Circle>());
    shapes.push_back(std::make_unique<Triangle>());
    shapes.push_back(std::make_unique<Circle>());

    std::unordered_map<std::string, int> counts;
    for (const auto& sh : shapes) {
        ++counts[typeid(*sh).name()];
    }

    for (const auto& [name, count] : counts) {
        std::cout << "  " << name << ": " << count << "\n";
    }

    std::cout << "\n  (имена искажены — name mangling)\n";
    std::cout << "  для читаемых имён — boost::typeindex или abi::__cxa_demangle\n";

    return 0;
}