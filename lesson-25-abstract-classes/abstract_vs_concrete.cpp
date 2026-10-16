#include <iostream>

// Абстрактный класс vs конкретный.

// Абстрактный: есть чистая виртуальная функция
class AbstractBase {
public:
    virtual ~AbstractBase() = default;
    virtual void action() const = 0;    // ← обязательна

    void helper() const {
        std::cout << "  helper из базового\n";
    }
};

// Абстрактный наследник, не реализовавший всё
class AbstractMiddle : public AbstractBase {
public:
    virtual void additional() const = 0;   // ещё одна обязательная
    // action() всё ещё не реализована — класс абстрактный
};

// Конкретный класс: реализует ВСЕ чистые функции
class Concrete : public AbstractMiddle {
public:
    void action() const override {
        std::cout << "  Concrete::action()\n";
    }
    void additional() const override {
        std::cout << "  Concrete::additional()\n";
    }
};

int main() {
    // AbstractBase a;      // ошибка
    // AbstractMiddle m;    // ошибка

    Concrete c;
    c.action();
    c.additional();
    c.helper();             // унаследовано от AbstractBase

    // Через базовый указатель
    AbstractBase* p = &c;
    p->action();            // виртуальный вызов — Concrete::action
    p->helper();

    return 0;
}