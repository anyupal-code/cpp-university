#include <iostream>
#include <cmath>

// Перегрузка операторов: +, -, *, ==, <<, ++.

class Vector2 {
public:
    double x, y;

    Vector2(double x, double y) : x(x), y(y) {}

    // Сложение
    Vector2 operator+(const Vector2& o) const {
        return {x + o.x, y + o.y};
    }

    // Вычитание
    Vector2 operator-(const Vector2& o) const {
        return {x - o.x, y - o.y};
    }

    // Умножение на скаляр
    Vector2 operator*(double k) const {
        return {x * k, y * k};
    }

    // Сравнение
    bool operator==(const Vector2& o) const {
        return x == o.x && y == o.y;
    }

    bool operator!=(const Vector2& o) const {
        return !(*this == o);
    }

    // Префиксный ++
    Vector2& operator++() {
        ++x; ++y;
        return *this;
    }

    // Постфиксный ++
    Vector2 operator++(int) {
        Vector2 old = *this;
        ++(*this);
        return old;
    }

    // Длина
    double length() const {
        return std::sqrt(x * x + y * y);
    }
};

// Вывод — вне класса, левый операнд ostream
std::ostream& operator<<(std::ostream& os, const Vector2& v) {
    os << "(" << v.x << ", " << v.y << ")";
    return os;
}

// Умножение на скаляр слева
Vector2 operator*(double k, const Vector2& v) {
    return v * k;
}

int main() {
    Vector2 a(1, 2);
    Vector2 b(3, 4);

    std::cout << "a = " << a << "\n";
    std::cout << "b = " << b << "\n\n";

    std::cout << "a + b    = " << a + b << "\n";
    std::cout << "b - a    = " << b - a << "\n";
    std::cout << "a * 2    = " << a * 2 << "\n";
    std::cout << "3 * b    = " << 3 * b << "\n\n";

    std::cout << "a == b?  " << (a == b) << "\n";
    std::cout << "a != b?  " << (a != b) << "\n\n";

    std::cout << "++a      = " << ++a << "\n";
    std::cout << "a++      = " << a++ << "\n";
    std::cout << "после    = " << a << "\n";

    std::cout << "\n|b| = " << b.length() << "\n";

    return 0;
}
