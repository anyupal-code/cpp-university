#include <iostream>

// Объявление, определение, вызов функций.

// Прототип — объявление до использования
int add(int a, int b);
int square(int x);
void print_result(int value);

int main() {
    int s = add(3, 5);
    print_result(s);

    std::cout << "square(7) = " << square(7) << "\n";

    return 0;
}

// Определения
int add(int a, int b) {
    return a + b;
}

int square(int x) {
    return x * x;
}

void print_result(int value) {
    std::cout << "Результат: " << value << "\n";
}