#include <iostream>
#include <vector>
#include <string>

// Объекты в vector: push_back, emplace_back, обход.

class Point {
private:
    int x_, y_;

public:
    Point(int x, int y) : x_(x), y_(y) {
        std::cout << "  [Point(" << x_ << ", " << y_ << ")]\n";
    }

    Point(const Point& o) : x_(o.x_), y_(o.y_) {
        std::cout << "  [Point copy]\n";
    }

    Point(Point&& o) noexcept : x_(o.x_), y_(o.y_) {
        std::cout << "  [Point move]\n";
    }

    int x() const { return x_; }
    int y() const { return y_; }
};

int main() {
    std::vector<Point> v;
    v.reserve(4);   // заранее выделим — избежим перевыделения

    std::cout << "push_back(Point(1, 2)):\n";
    v.push_back(Point(1, 2));

    std::cout << "\nemplace_back(3, 4):\n";
    v.emplace_back(3, 4);

    std::cout << "\nemplace_back(5, 6):\n";
    v.emplace_back(5, 6);

    std::cout << "\nОбход:\n";
    for (const auto& p : v) {
        std::cout << "  (" << p.x() << ", " << p.y() << ")\n";
    }

    std::cout << "\nДоступ:\n";
    std::cout << "  front: (" << v.front().x() << ", " << v.front().y() << ")\n";
    std::cout << "  back:  (" << v.back().x() << ", " << v.back().y() << ")\n";
    std::cout << "  v[1]:  (" << v[1].x() << ", " << v[1].y() << ")\n";

    return 0;
}
