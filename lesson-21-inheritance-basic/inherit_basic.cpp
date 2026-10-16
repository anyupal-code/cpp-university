#include <iostream>
#include <string>

// Базовое наследование: базовый класс и наследник.

class Animal {
protected:
    std::string name_;

public:
    Animal(const std::string& name) : name_(name) {
        std::cout << "  Animal(" << name_ << ") создан\n";
    }

    void eat() const {
        std::cout << "  " << name_ << " ест\n";
    }

    void sleep() const {
        std::cout << "  " << name_ << " спит\n";
    }
};

class Dog : public Animal {
public:
    Dog(const std::string& name) : Animal(name) {
        std::cout << "  Dog(" << name_ << ") создан\n";
    }

    void bark() const {
        std::cout << "  " << name_ << " лает: Гав!\n";
    }
};

int main() {
    std::cout << "=== Создание Dog ===\n";
    Dog d("Бим");
    std::cout << "\n";

    std::cout << "Унаследованные методы:\n";
    d.eat();
    d.sleep();

    std::cout << "\nСвой метод:\n";
    d.bark();

    std::cout << "\n=== Уничтожение ===\n";

    return 0;
}