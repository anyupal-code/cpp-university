#include <iostream>
#include <string>

// Перегрузка функций: одно имя, разные параметры.

int add(int a, int b) {
    std::cout << "[int add] ";
    return a + b;
}

double add(double a, double b) {
    std::cout << "[double add] ";
    return a + b;
}

int add(int a, int b, int c) {
    std::cout << "[int add x3] ";
    return a + b + c;
}

std::string add(const std::string& a, const std::string& b) {
    std::cout << "[string add] ";
    return a + b;
}

int main() {
    std::cout << add(3, 5) << "\n";
    std::cout << add(3.5, 5.7) << "\n";
    std::cout << add(1, 2, 3) << "\n";
    std::cout << add(std::string("Hello, "), std::string("World!")) << "\n";

    return 0;
}