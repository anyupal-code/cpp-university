#include <iostream>

// Чистый виртуальный деструктор.

class AbstractBase {
public:
    virtual ~AbstractBase() = 0;   // чистая — класс абстрактный
};

// ОБЯЗАТЕЛЬНО тело — иначе ошибка линковки
AbstractBase::~AbstractBase() = default;

class Derived : public AbstractBase {
public:
    Derived() { std::cout << "  Derived()\n"; }
    ~Derived() override { std::cout << "  ~Derived()\n"; }
};

// Класс-интерфейс с полем (не чистый интерфейс)
class BaseWithField {
    int id_;
public:
    explicit BaseWithField(int id) : id_(id) {}
    virtual ~BaseWithField() = default;
    int id() const { return id_; }
};

int main() {
    // AbstractBase b;    // ошибка: нельзя создать объект

    std::cout << "=== Создание Derived ===\n";
    {
        Derived d;
    }
    std::cout << "=== Уничтожено ===\n";

    std::cout << "\n=== Через базовый указатель ===\n";
    {
        AbstractBase* p = new Derived;
        delete p;   // ~Derived + ~AbstractBase
    }

    std::cout << "\n=== Комбинация: базовый с полями + абстрактный деструктор ===\n";
    {
        BaseWithField* p = new BaseWithField(42);
        std::cout << "  id = " << p->id() << "\n";
        delete p;
    }

    return 0;
}