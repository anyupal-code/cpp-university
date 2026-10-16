#include <iostream>
#include <unordered_set>
#include <unordered_map>

// Свой хеш для пользовательского типа.

struct Point {
    int x, y;

    bool operator==(const Point& o) const {
        return x == o.x && y == o.y;
    }
};

// Хеш-функция для Point
struct PointHash {
    std::size_t operator()(const Point& p) const noexcept {
        std::size_t h1 = std::hash<int>{}(p.x);
        std::size_t h2 = std::hash<int>{}(p.y);
        return h1 ^ (h2 << 1);   // простая комбинация
    }
};

// Вывод точки
std::ostream& operator<<(std::ostream& os, const Point& p) {
    return os << "(" << p.x << ", " << p.y << ")";
}

int main() {
    std::unordered_set<Point, PointHash> points;

    points.insert({1, 2});
    points.insert({3, 4});
    points.insert({1, 2});    // дубликат — не добавится
    points.insert({5, 6});

    std::cout << "Точек: " << points.size() << "\n\n";

    std::cout << "Содержимое:\n";
    for (const auto& p : points) {
        std::cout << "  " << p << "\n";
    }

    // Проверка наличия
    std::cout << "\ncontains((1,2))? "
              << points.contains({1, 2}) << "\n";
    std::cout << "contains((9,9))? "
              << points.contains({9, 9}) << "\n\n";

    // unordered_map с Point как ключом
    std::unordered_map<Point, std::string, PointHash> labels;
    labels[{0, 0}] = "начало";
    labels[{10, 10}] = "конец";

    std::cout << "labels[(0,0)] = " << labels[{0, 0}] << "\n";
    std::cout << "labels[(10,10)] = " << labels[{10, 10}] << "\n";

    return 0;
}