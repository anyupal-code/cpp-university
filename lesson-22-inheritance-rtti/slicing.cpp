#include <iostream>
#include <string>

// Срезка объектов.

class Animal {
protected:
    std::string name_;
public:
    explicit Animal(const std::string& n) : name_(n) {}
    virtual ~Animal() = default;

    virtual std::string voice() const {
        return "...";
    }
};

class Dog : public Animal {
    std::string breed_;
public:
    Dog(const std::string& n, const std::string& b)
        : Animal(n), breed_(b) {}

    std::string voice() const override {
        return "Гав";
    }

    std::string breed() const { return breed_; }
};

void by_value(Animal a) {          // ← СРЕЗКА!
    std::cout << "  by_value: " << a.voice() << "\n";
}

void by_reference(const Animal& a) {   // ← ОК
    std::cout << "  by_reference: " << a.voice() << "\n";
}

int main() {
    Dog d("Бим", "овчарка");

    std::cout << "Оригинал: " << d.voice()
              << " (" << d.breed() << ")\n\n";

    std::cout << "=== Срезка при копировании ===\n";
    Animal a = d;                  // срезка!
    std::cout << "a.voice() = " << a.voice()
              << " (потеряно: breed, voice стал базовым)\n\n";

    std::cout << "=== Без срезки ===\n";
    by_value(d);                   // срезка внутри функции
    by_reference(d);               // ок — ссылка

    std::cout << "\n=== Правильно ===\n";
    const Animal& ref = d;         // ссылка
    std::cout << "ref.voice() = " << ref.voice() << "\n";

    Animal* ptr = &d;              // указатель
    std::cout << "ptr->voice() = " << ptr->voice() << "\n";

    return 0;
}