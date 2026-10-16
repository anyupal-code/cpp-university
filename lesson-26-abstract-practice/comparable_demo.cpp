#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>

// Интерфейс IComparable.

class IComparable {
public:
    virtual ~IComparable() = default;
    virtual int compare(const IComparable& o) const = 0;
};

class Person : public IComparable {
    std::string name_;
    int age_;
public:
    Person(std::string name, int age)
        : name_(std::move(name)), age_(age) {}

    int compare(const IComparable& o) const override {
        const auto* other = dynamic_cast<const Person*>(&o);
        if (!other) throw std::invalid_argument("не Person");

        if (age_ != other->age_) return age_ - other->age_;
        return name_.compare(other->name_);
    }

    const std::string& name() const { return name_; }
    int age() const { return age_; }
};

std::ostream& operator<<(std::ostream& os, const Person& p) {
    return os << p.name() << " (" << p.age() << ")";
}

int main() {
    Person a("Иван", 30);
    Person b("Мария", 25);
    Person c("Пётр", 30);

    std::cout << "a = " << a << "\n";
    std::cout << "b = " << b << "\n";
    std::cout << "c = " << c << "\n\n";

    std::cout << "=== Сравнения ===\n";
    std::cout << "a.compare(b) = " << a.compare(b) << " (>0, a > b)\n";
    std::cout << "b.compare(a) = " << b.compare(a) << " (<0)\n";
    std::cout << "a.compare(c) = " << a.compare(c) << " (0? нет: age равны, имя Иван vs Пётр)\n";
    std::cout << "a.compare(a) = " << a.compare(a) << " (=0)\n\n";

    std::vector<Person> people = {
        {"Иван", 30},
        {"Мария", 25},
        {"Пётр", 30},
        {"Анна", 28}
    };

    std::sort(people.begin(), people.end(),
              [](const Person& x, const Person& y) {
                  return x.compare(y) < 0;
              });

    std::cout << "=== Отсортировано ===\n";
    for (const auto& p : people) {
        std::cout << "  " << p << "\n";
    }

    return 0;
}