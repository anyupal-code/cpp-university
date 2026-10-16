#include <iostream>
#include <memory>
#include <vector>
#include <string>

// Задача 5. Тренировочные вопросы.

// === Вопрос 1. Порядок конструкторов и деструкторов ===
class A {
public:
    A()  { std::cout << "A() "; }
    ~A() { std::cout << "~A() "; }
};

class B : public A {
public:
    B()  { std::cout << "B() "; }
    ~B() { std::cout << "~B() "; }
};

// === Вопрос 2. Виртуальный деструктор ===
class WithoutVirtual {
public:
    ~WithoutVirtual() { std::cout << "  ~WithoutVirtual (наследник утечёт)\n"; }
};

class DerivedNoVirt : public WithoutVirtual {
public:
    ~DerivedNoVirt() { std::cout << "  ~DerivedNoVirt (не вызовется)\n"; }
};

class WithVirtual {
public:
    virtual ~WithVirtual() { std::cout << "  ~WithVirtual\n"; }
};

class DerivedVirt : public WithVirtual {
public:
    ~DerivedVirt() override { std::cout << "  ~DerivedVirt\n"; }
};

// === Вопрос 3. Срезка ===
class Shape {
public:
    virtual std::string name() const { return "Shape"; }
    virtual ~Shape() = default;
};

class Circle : public Shape {
public:
    std::string name() const override { return "Circle"; }
};

void by_value(Shape s)         { std::cout << "  by_value: " << s.name() << "\n"; }
void by_ref(const Shape& s)    { std::cout << "  by_ref:   " << s.name() << "\n"; }

// === Вопрос 6. unique_ptr vs shared_ptr ===
void unique_demo() {
    auto p = std::make_unique<int>(42);
    // auto q = p;              // ошибка — нельзя копировать
    auto q = std::move(p);      // ок — перемещение
    std::cout << "  unique_ptr после move: p = "
              << (p == nullptr ? "nullptr" : "valid") << "\n";
}

void shared_demo() {
    auto p = std::make_shared<int>(42);
    auto q = p;
    std::cout << "  shared_ptr use_count: " << p.use_count() << "\n";
}

// === Вопрос 7. weak_ptr ===
void weak_demo() {
    auto sp = std::make_shared<int>(42);
    std::weak_ptr<int> wp = sp;

    std::cout << "  wp.expired() до reset: " << wp.expired() << "\n";
    sp.reset();
    std::cout << "  wp.expired() после reset: " << wp.expired() << "\n";
}

int main() {
    std::cout << "=== 1. Порядок конструкторов и деструкторов ===\n";
    { B b; }
    std::cout << "\n";

    std::cout << "\n=== 2. Виртуальный деструктор ===\n";
    {
        WithoutVirtual* p = new DerivedNoVirt;
        delete p;
    }
    {
        WithVirtual* p = new DerivedVirt;
        delete p;
    }

    std::cout << "\n=== 3. Срезка ===\n";
    Circle c;
    by_value(c);    // Shape (срезка)
    by_ref(c);      // Circle (без срезки)

    std::cout << "\n=== 4. override ===\n";
    std::cout << "  override — компилятор проверит переопределение\n";
    std::cout << "  перегрузка — разные параметры, одно имя\n";

    std::cout << "\n=== 5. Правило пяти ===\n";
    std::cout << "  деструктор + копирующий + move + копирующее присв. + move присв.\n";

    std::cout << "\n=== 6. unique_ptr vs shared_ptr ===\n";
    unique_demo();
    shared_demo();

    std::cout << "\n=== 7. weak_ptr ===\n";
    weak_demo();

    std::cout << "\n=== 8. dynamic_cast vs static_cast ===\n";
    std::cout << "  dynamic_cast — проверяет тип, медленнее\n";
    std::cout << "  static_cast — без проверки, быстрее\n";

    std::cout << "\n=== 9. const-метод ===\n";
    std::cout << "  не меняет объект, вызывается у const-объектов\n";

    std::cout << "\n=== 10. RAII ===\n";
    std::cout << "  ресурс захватывается в конструкторе, освобождается в деструкторе\n";

    return 0;
}