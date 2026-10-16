#include <iostream>
#include <string>
#include <vector>
#include <memory>

// Виртуальные функции и полиморфизм.

class Animal {
protected:
    std::string name_;

public:
    explicit Animal(const std::string& n) : name_(n) {}
    virtual ~Animal() = default;

    virtual std::string voice() const {
        return "...";
    }

    void print() const {
        std::cout << "  " << name_ << " говорит: " << voice() << "\n";
    }
};

class Dog : public Animal {
public:
    explicit Dog(const std::string& n) : Animal(n) {}

    std::string voice() const override {
        return "Гав";
    }
};

class Cat : public Animal {
public:
    explicit Cat(const std::string& n) : Animal(n) {}

    std::string voice() const override {
        return "Мяу";
    }
};

class Cow : public Animal {
public:
    explicit Cow(const std::string& n) : Animal(n) {}

    std::string voice() const override {
        return "Му";
    }
};

int main() {
    std::cout << "=== Прямые вызовы ===\n";
    Dog d("Бим");
    Cat c("Мурка");
    Cow m("Зорька");

    d.print();
    c.print();
    m.print();

    std::cout << "\n=== Полиморфная коллекция ===\n";
    std::vector<std::unique_ptr<Animal>> animals;
    animals.push_back(std::make_unique<Dog>("Рекс"));
    animals.push_back(std::make_unique<Cat>("Барсик"));
    animals.push_back(std::make_unique<Cow>("Бурёнка"));
    animals.push_back(std::make_unique<Dog>("Шарик"));

    for (const auto& a : animals) {
        a->print();    // виртуальный вызов
    }

    return 0;
}