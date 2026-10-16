#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

// Иерархия сотрудников.

class Employee {
protected:
    std::string name_;
    double base_salary_;

public:
    Employee(std::string name, double base)
        : name_(std::move(name)), base_salary_(base) {}

    virtual ~Employee() = default;    // ВАЖНО: виртуальный

    virtual double salary() const {
        return base_salary_;
    }

    virtual std::string position() const {
        return "Сотрудник";
    }

    const std::string& name() const { return name_; }

    void print() const {
        std::cout << std::setw(10) << std::left << name_
                  << std::setw(18) << position()
                  << " оклад: " << std::fixed << std::setprecision(2)
                  << salary() << "\n";
    }
};

class Manager : public Employee {
    double bonus_;
public:
    Manager(std::string name, double base, double bonus)
        : Employee(std::move(name), base), bonus_(bonus) {}

    double salary() const override {
        return base_salary_ + bonus_;
    }

    std::string position() const override {
        return "Менеджер";
    }
};

class Intern : public Employee {
public:
    Intern(std::string name, double base)
        : Employee(std::move(name), base) {}

    double salary() const override {
        return base_salary_ * 0.5;    // полставки
    }

    std::string position() const override {
        return "Стажёр";
    }
};

int main() {
    std::vector<Employee*> staff;
    staff.push_back(new Employee("Иван", 50000));
    staff.push_back(new Manager("Мария", 70000, 20000));
    staff.push_back(new Intern("Пётр", 30000));

    std::cout << "=== Сотрудники ===\n";
    for (auto* e : staff) {
        e->print();
    }

    std::cout << "\n=== Уборка ===\n";
    for (auto* e : staff) {
        delete e;    // виртуальный деструктор — всё корректно
    }

    return 0;
}