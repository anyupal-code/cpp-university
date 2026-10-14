#include <iostream>

// Простой класс с инкапсуляцией.

class Point {
private:
    int x_;
    int y_;

public:
    Point(int x, int y) : x_(x), y_(y) {}

    int get_x() const { return x_; }
    int get_y() const { return y_; }

    void set_x(int x) { x_ = x; }
    void set_y(int y) { y_ = y; }

    void move(int dx, int dy) {
        x_ += dx;
        y_ += dy;
    }

    void print() const {
        std::cout << "(" << x_ << ", " << y_ << ")\n";
    }
};

int main() {
    Point p(3, 5);
    std::cout << "p = ";
    p.print();

    std::cout << "p.get_x() = " << p.get_x() << "\n";
    std::cout << "p.get_y() = " << p.get_y() << "\n\n";

    p.set_x(10);
    p.set_y(20);
    std::cout << "После set: ";
    p.print();

    p.move(1, 1);
    std::cout << "После move(1, 1): ";
    p.print();

    return 0;
}
