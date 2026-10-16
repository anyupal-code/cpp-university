#include <iostream>
#include <vector>
#include <memory>

// Чистые виртуальные функции.

class Animal {
protected:
    std::string name_;
public:
    explicit Animal(std::string n) : name_(std::move(n)) {}
    virtual ~Animal() = default;

    // Обязательные — pure virtual
    virtual std::string voice() const = 0;
    virtual int legs() const = 0;

    // Необязательный — обычная virtual
    virtual std::string category() const {
        return "Животное";
    }

    // Не виртуальный
    const std::string& name() const { return name_; }

    void print() const {
        std::cout << "  " << name_
                  << " [" << category() << "]"
                  << ", ног: " << legs()
                  << ", голос: " << voice() << "\n";
    }
};

class Dog : public Animal {
public:
    explicit Dog(std::string n) : Animal(std::move(n)) {}

    std::string voice() const override { return "Гав"; }
    int legs() const override { return 4; }

    std::string category() const override { return "Собака"; }
};

class Bird : public Animal {
public:
    explicit Bird(std::string n) : Animal(std::move(n)) {}

    std::string voice() const override { return "Чик-чирик"; }
    int legs() const override { return 2; }
    // category() не переопределён — будет "Животное"
};

int main() {
    std::vector<std::unique_ptr<Animal>> animals;
    animals.push_back(std::make_unique<Dog>("Бим"));
    animals.push_back(std::make_unique<Bird>("Кеша"));
    animals.push_back(std::make_unique<Dog>("Рекс"));

    std::cout << "=== Все животные ===\n";
    for (const auto& a : animals) {
        a->print();
    }

    return 0;
}