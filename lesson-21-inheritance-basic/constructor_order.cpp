#include <iostream>
#include <string>

// Порядок вызова конструкторов и деструкторов.

class Base {
public:
    Base() {
        std::cout << "  Base() — конструктор\n";
    }
    ~Base() {
        std::cout << "  ~Base() — деструктор\n";
    }
};

class Middle : public Base {
public:
    Middle() {
        std::cout << "  Middle() — конструктор\n";
    }
    ~Middle() {
        std::cout << "  ~Middle() — деструктор\n";
    }
};

class Derived : public Middle {
public:
    Derived() {
        std::cout << "  Derived() — конструктор\n";
    }
    ~Derived() {
        std::cout << "  ~Derived() — деструктор\n";
    }
};

int main() {
    std::cout << "=== Создание объекта ===\n";
    {
        Derived d;
        std::cout << "  (объект живёт)\n";
    }
    std::cout << "=== Объект уничтожен ===\n";

    std::cout << "\n=== Итог ===\n";
    std::cout << "Конструкторы: Base -> Middle -> Derived\n";
    std::cout << "Деструкторы:  Derived -> Middle -> Base\n";

    return 0;
}