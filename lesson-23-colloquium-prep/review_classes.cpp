#include <iostream>
#include <string>
#include <utility>

// Обзор: классы, конструкторы, explicit, const-методы.

class Person {
private:
    std::string name_;
    int age_;

public:
    // Конструктор по умолчанию
    Person() : name_("Неизвестно"), age_(0) {
        std::cout << "  [default]\n";
    }

    // С параметрами
    Person(std::string name, int age)
        : name_(std::move(name)), age_(age) {
        std::cout << "  [Person(\"" << name_ << "\", " << age_ << ")]\n";
    }

    // explicit: запрет неявного преобразования
    explicit Person(std::string name)
        : name_(std::move(name)), age_(18) {
        std::cout << "  [explicit Person(\"" << name_ << "\")]\n";
    }

    const std::string& name() const { return name_; }
    int age() const { return age_; }

    void set_age(int a) {
        if (a < 0 || a > 150) {
            std::cout << "  неверный возраст: " << a << "\n";
            return;
        }
        age_ = a;
    }

    void print() const {
        std::cout << "  " << name_ << ", " << age_ << " лет\n";
    }
};

void print_person(const Person& p) {
    p.print();
}

int main() {
    std::cout << "=== Создание объектов ===\n";
    Person p1;
    Person p2("Иван", 25);
    Person p3("Мария");
    std::cout << "\n";

    std::cout << "=== Свойства ===\n";
    p2.print();
    p2.set_age(26);
    p2.print();
    p2.set_age(200);    // неверно
    p2.print();

    // Person p4 = "Пётр";    // ошибка: explicit
    Person p4("Пётр");         // ок

    std::cout << "\n=== const-методы ===\n";
    const Person cp("Анна", 20);
    cp.print();
    // cp.set_age(30);        // ошибка: set_age не const

    std::cout << "\n=== Передача по const& ===\n";
    print_person(p2);

    return 0;
}