#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>

// Интерфейсы через абстрактные классы.

// Интерфейс «можно напечатать»
class IPrintable {
public:
    virtual ~IPrintable() = default;
    virtual void print() const = 0;
};

// Интерфейс «можно сериализовать»
class ISerializable {
public:
    virtual ~ISerializable() = default;
    virtual std::string serialize() const = 0;
};

// Класс реализует два интерфейса
class Person : public IPrintable, public ISerializable {
    std::string name_;
    int age_;
public:
    Person(std::string name, int age)
        : name_(std::move(name)), age_(age) {}

    void print() const override {
        std::cout << "Person(" << name_ << ", " << age_ << ")\n";
    }

    std::string serialize() const override {
        return name_ + ";" + std::to_string(age_);
    }
};

class Book : public IPrintable, public ISerializable {
    std::string title_;
    int pages_;
public:
    Book(std::string title, int pages)
        : title_(std::move(title)), pages_(pages) {}

    void print() const override {
        std::cout << "Book(\"" << title_ << "\", " << pages_ << " стр.)\n";
    }

    std::string serialize() const override {
        return title_ + ";" + std::to_string(pages_);
    }
};

int main() {
    std::vector<std::unique_ptr<IPrintable>> printables;
    printables.push_back(std::make_unique<Person>("Иван", 25));
    printables.push_back(std::make_unique<Book>("Pascal", 300));
    printables.push_back(std::make_unique<Person>("Мария", 30));

    std::cout << "=== Печать ===\n";
    for (const auto& p : printables) {
        p->print();
    }

    // Отдельно сериализация
    std::vector<std::unique_ptr<ISerializable>> serializables;
    serializables.push_back(std::make_unique<Person>("Пётр", 28));
    serializables.push_back(std::make_unique<Book>("C++", 500));

    std::cout << "\n=== Сериализация ===\n";
    for (const auto& s : serializables) {
        std::cout << "  " << s->serialize() << "\n";
    }

    return 0;
}