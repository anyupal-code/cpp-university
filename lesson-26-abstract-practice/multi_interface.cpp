#include <iostream>
#include <memory>
#include <vector>
#include <string>

// Два интерфейса у одного класса.

class IPrintable {
public:
    virtual ~IPrintable() = default;
    virtual void print() const = 0;
};

class ISerializable {
public:
    virtual ~ISerializable() = default;
    virtual std::string serialize() const = 0;
};

// Класс реализует оба интерфейса
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
        return "Person;" + name_ + ";" + std::to_string(age_);
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
        return "Book;" + title_ + ";" + std::to_string(pages_);
    }
};

int main() {
    // Через IPrintable
    std::vector<std::unique_ptr<IPrintable>> printables;
    printables.push_back(std::make_unique<Person>("Иван", 25));
    printables.push_back(std::make_unique<Book>("Pascal", 300));
    printables.push_back(std::make_unique<Person>("Мария", 30));

    std::cout << "=== Печать ===\n";
    for (const auto& p : printables) {
        p->print();
    }

    // Через ISerializable
    std::vector<std::unique_ptr<ISerializable>> serializables;
    serializables.push_back(std::make_unique<Person>("Пётр", 28));
    serializables.push_back(std::make_unique<Book>("C++", 500));

    std::cout << "\n=== Сериализация ===\n";
    for (const auto& s : serializables) {
        std::cout << "  " << s->serialize() << "\n";
    }

    // Один объект — в двух «ролях»
    std::cout << "\n=== Один объект — два интерфейса ===\n";
    auto p = std::make_shared<Person>("Анна", 22);

    IPrintable* pr = p.get();
    ISerializable* sr = p.get();

    pr->print();
    std::cout << "  serialized: " << sr->serialize() << "\n";

    return 0;
}