#include <iostream>
#include <vector>
#include <algorithm>

// Операторы сравнения: старый способ и C++20 (<=>).

class Point {
private:
    int x_, y_;

public:
    Point(int x, int y) : x_(x), y_(y) {}

    int x() const { return x_; }
    int y() const { return y_; }

    // Все операторы сравнения через C++20
    auto operator<=>(const Point&) const = default;

    // == нужен отдельно для C++20 (по умолчанию генерируется)
    // bool operator==(const Point&) const = default;
};

std::ostream& operator<<(std::ostream& os, const Point& p) {
    return os << "(" << p.x() << ", " << p.y() << ")";
}

int main() {
    Point a(1, 2);
    Point b(1, 3);
    Point c(2, 0);

    std::cout << "a = " << a << "\n";
    std::cout << "b = " << b << "\n";
    std::cout << "c = " << c << "\n\n";

    std::cout << "a == b? " << (a == b) << "\n";
    std::cout << "a != b? " << (a != b) << "\n";
    std::cout << "a <  b? " << (a <  b) << "\n";
    std::cout << "a <= b? " << (a <= b) << "\n";
    std::cout << "b >  c? " << (b >  c) << "\n\n";

    // Сортировка — работает автоматически
    std::vector<Point> v = {c, a, b};
    std::sort(v.begin(), v.end());

    std::cout << "Отсортировано: ";
    for (const auto& p : v) std::cout << p << " ";
    std::cout << "\n";

    return 0;
}
