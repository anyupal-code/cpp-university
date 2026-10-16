#include <iostream>
#include <string>
#include <vector>

// Наследование vs композиция.

// === НАСЛЕДОВАНИЕ: «is-a» ===
// Собака ЯВЛЯЕТСЯ животным

class Animal {
protected:
    std::string name_;
public:
    Animal(const std::string& n) : name_(n) {}
    void breathe() const {
        std::cout << "  " << name_ << " дышит\n";
    }
};

class Dog : public Animal {       // Dog — это Animal
public:
    Dog(const std::string& n) : Animal(n) {}
    void bark() const {
        std::cout << "  " << name_ << " лает\n";
    }
};

// === КОМПОЗИЦИЯ: «has-a» ===
// Машина СОДЕРЖИТ двигатель и колёса

class Engine {
public:
    void start() const {
        std::cout << "  Двигатель запущен\n";
    }
};

class Wheel {
    int size_;
public:
    explicit Wheel(int size) : size_(size) {}
    int size() const { return size_; }
};

class Car {
private:
    Engine engine_;                // Car содержит Engine
    std::vector<Wheel> wheels_;    // и 4 колеса
    std::string model_;

public:
    Car(const std::string& model)
        : model_(model) {
        for (int i = 0; i < 4; ++i) {
            wheels_.emplace_back(15);
        }
    }

    void drive() const {
        std::cout << "  " << model_ << " едет на "
                  << wheels_.size() << " колёсах\n";
    }
};

int main() {
    std::cout << "=== Наследование (is-a) ===\n";
    Dog d("Бим");
    d.breathe();     // унаследовано
    d.bark();        // своё

    std::cout << "\n=== Композиция (has-a) ===\n";
    Car c("Лада");
    c.drive();

    // Плохо бы было: class Car : public Engine — «Car является Engine»? Нет.

    std::cout << "\n=== Правило ===\n";
    std::cout << "«является»  -> наследование\n";
    std::cout << "«содержит» -> композиция\n";

    return 0;
}