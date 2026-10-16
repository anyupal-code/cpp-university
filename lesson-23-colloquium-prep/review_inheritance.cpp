#include <iostream>
#include <string>

// Обзор: иерархия, порядок вызова, виртуальный деструктор.

class Animal {
protected:
    std::string name_;

public:
    explicit Animal(std::string name)
        : name_(std::move(name)) {
        std::cout << "  Animal(\"" << name_ << "\")\n";
    }

    virtual ~Animal() {
        std::cout << "  ~Animal(\"" << name_ << "\")\n";
    }

    virtual std::string voice() const {
        return "...";
    }

    const std::string& name() const { return name_; }

    void print() const {
        std::cout << "  " << name_ << ": " << voice() << "\n";
    }
};

class Dog : public Animal {
    std::string breed_;
public:
    Dog(std::string name, std::string breed)
        : Animal(std::move(name)), breed_(std::move(breed)) {
        std::cout << "  Dog(\"" << name_ << "\", \"" << breed_ << "\")\n";
    }

    ~Dog() override {
        std::cout << "  ~Dog(\"" << name_ << "\")\n";
    }

    std::string voice() const override {
        return "Гав";
    }
};

int main() {
    std::cout << "=== Создание Dog ===\n";
    {
        Dog d("Бим", "овчарка");
        std::cout << "\n";
        d.print();
    }
    std::cout << "=== Уничтожение ===\n";

    std::cout << "\n=== Через базовый указатель ===\n";
    {
        Animal* p = new Dog("Рекс", "лабрадор");
        p->print();
        delete p;    // ~Dog + ~Animal (виртуальный деструктор)
    }

    return 0;
}