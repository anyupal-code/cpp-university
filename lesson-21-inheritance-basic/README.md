# Урок 21. Наследование: базовое

## Цель

Освоить наследование — механизм повторного использования классов.
Понять порядок вызова конструкторов и деструкторов, разницу между
наследованием и композицией, роль виртуального деструктора.

## Ключевые понятия

- **Базовый класс (родитель)** — от кого наследуют.
- **Производный класс (наследник)** — кто наследует.
- **`public` наследование** — «is-a».
- **`protected`** — доступ для класса и наследников.
- **`override`** — явное переопределение метода.
- **Виртуальный деструктор** — правильное удаление через базовый указатель.
- **Наследование vs композиция** — «is-a» vs «has-a».

---

## 1. Что такое наследование

**Наследование** — способ создать новый класс на основе существующего,
добавив или изменив поведение.

```
       Animal
       ├── Dog
       └── Cat
```

- **`Animal`** — базовый класс.
- **`Dog`, `Cat`** — наследники.
- Наследники получают **все** `public` и `protected` члены родителя.
- Могут **добавлять** свои поля и методы.
- Могут **переопределять** поведение.

**Отношение:** «Dog **является** Animal» — «is-a».

---

## 2. Синтаксис

```cpp
class Animal {
protected:
    std::string name_;

public:
    Animal(const std::string& name) : name_(name) {}

    void eat() const {
        std::cout << name_ << " ест\n";
    }

    void sleep() const {
        std::cout << name_ << " спит\n";
    }
};

class Dog : public Animal {    // ← public наследование
public:
    Dog(const std::string& name) : Animal(name) {}   // вызвать родительский конструктор

    void bark() const {
        std::cout << name_ << " лает\n";
    }
};
```

Использование:

```cpp
Dog d("Бим");
d.eat();      // унаследован
d.sleep();    // унаследован
d.bark();     // свой
```

---

## 3. Типы наследования

| Тип | Синтаксис | Что происходит |
|---|---|---|
| **public** | `class D : public B` | `public` → `public`, `protected` → `protected` |
| **protected** | `class D : protected B` | `public` и `protected` → `protected` |
| **private** | `class D : private B` | всё → `private` |

**В 99% случаев — `public`.** Остальные — для особых случаев (редко).

**Правило:** если не уверен — `public`.

---

## 4. Уровни доступа

| Уровень | Кто видит |
|---|---|
| `public` | все |
| `protected` | сам класс + наследники |
| `private` | только сам класс |

**Что важно:**

- **`private`** — **наследник не видит**.
- **`protected`** — наследник видит, но снаружи не видно.
- **`public`** — видят все.

**Правило:**

- Поля — `private` (или `protected`, если наследники должны иметь доступ).
- Методы — `public` (интерфейс) или `private`/`protected` (внутренние).

```cpp
class Base {
private:
    int private_field_;      // наследник не видит

protected:
    int protected_field_;    // наследник видит

public:
    int public_field_;       // все видят
};

class Derived : public Base {
    void f() {
        // private_field_ = 1;    // ошибка
        protected_field_ = 2;     // ок
        public_field_ = 3;        // ок
    }
};
```

---

## 5. Порядок вызова конструкторов и деструкторов

**При создании объекта наследника:**

1. Сначала вызывается **конструктор базового класса**.
2. Потом — **конструктор наследника**.

**При уничтожении:**

1. Сначала — **деструктор наследника**.
2. Потом — **деструктор базового класса**.

**Мнемоника:** конструкторы — сверху вниз, деструкторы — снизу вверх.

```cpp
class Base {
public:
    Base()  { std::cout << "Base()\n"; }
    ~Base() { std::cout << "~Base()\n"; }
};

class Derived : public Base {
public:
    Derived()  { std::cout << "Derived()\n"; }
    ~Derived() { std::cout << "~Derived()\n"; }
};

int main() {
    Derived d;
}
// Вывод:
// Base()
// Derived()
// ~Derived()
// ~Base()
```

---

## 6. Вызов родительского конструктора

Через **список инициализации**:

```cpp
class Animal {
protected:
    std::string name_;
public:
    Animal(const std::string& name) : name_(name) {}
};

class Dog : public Animal {
public:
    Dog(const std::string& name) : Animal(name) {}   // ← вызов
};
```

**Что важно:**

- Если у родителя **есть конструктор с параметрами** — наследник
  обязан его вызвать.
- Если у родителя **конструктор по умолчанию** — можно не вызывать
  (вызовется автоматически).
- **Порядок** в списке инициализации не влияет на порядок вызова —
  поля инициализируются в порядке объявления, базы — **раньше** полей наследника.

---

## 7. Переопределение методов

Наследник может **переопределить** метод родителя:

```cpp
class Animal {
public:
    void voice() const {
        std::cout << "...\n";
    }
};

class Dog : public Animal {
public:
    void voice() const {
        std::cout << "Гав\n";
    }
};
```

**Осторожно:** без `virtual` — это **не полиморфизм**. Вызов через
указатель на родителя пойдёт в **родительский** метод.

```cpp
Dog d;
Animal* p = &d;
p->voice();    // "...", не "Гав" — потому что voice не virtual
```

**Правильно — с `virtual`** (подробно в уроке 22):

```cpp
class Animal {
public:
    virtual void voice() const {
        std::cout << "...\n";
    }
};

class Dog : public Animal {
public:
    void voice() const override {    // ← override
        std::cout << "Гав\n";
    }
};
```

**Правило:** переопределяешь метод — пиши `override`. Компилятор
проверит, что ты действительно переопределяешь.

---

## 8. Виртуальный деструктор

**Проблема:**

```cpp
class Base {
public:
    ~Base() { std::cout << "~Base\n"; }
};

class Derived : public Base {
    int* data_;
public:
    Derived() : data_(new int[100]) {}
    ~Derived() {
        delete[] data_;
        std::cout << "~Derived\n";
    }
};

Base* p = new Derived;
delete p;   // вызовется ~Base, но НЕ ~Derived — утечка!
```

**Решение:** сделать деструктор родителя **виртуальным**:

```cpp
class Base {
public:
    virtual ~Base() = default;
};

class Derived : public Base {
    int* data_;
public:
    Derived() : data_(new int[100]) {}
    ~Derived() override {
        delete[] data_;
    }
};

Base* p = new Derived;
delete p;   // ~Derived + ~Base — правильно
```

**Правило:** если класс предназначен для наследования и удаления
через базовый указатель — **деструктор обязан быть `virtual`**.

**Когда не нужен:**

- Класс не предназначен для наследования.
- Объекты не удаляются через базовый указатель.

**Совет:** если сомневаешься — делай `virtual`.

---

## 9. Наследование vs композиция

**Наследование — «is-a»:**

```cpp
class Car : public Vehicle { ... };   // Car — это Vehicle
```

**Композиция — «has-a»:**

```cpp
class Car {
    Engine engine_;    // Car содержит Engine
    Wheel wheels_[4];
};
```

**Правило:**

- «является» → наследование.
- «содержит» → композиция.

**Ошибка новичков:** использовать наследование там, где нужно
«содержит».

```cpp
// Плохо: Stack наследует vector — но Stack не «является» vector
class Stack : public std::vector<int> { ... };

// Хорошо: Stack содержит vector
class Stack {
    std::vector<int> data_;
public:
    void push(int x) { data_.push_back(x); }
    // ...
};
```

**Композиция предпочтительнее**, если нет чёткого «is-a».

---

## 10. Типичные задачи

### Иерархия «Фигуры»

```cpp
class Shape {
public:
    virtual ~Shape() = default;
    virtual double area() const = 0;
    virtual std::string name() const = 0;
};

class Circle : public Shape {
    double r_;
public:
    Circle(double r) : r_(r) {}
    double area() const override { return 3.14159 * r_ * r_; }
    std::string name() const override { return "Круг"; }
};

class Rectangle : public Shape {
    double w_, h_;
public:
    Rectangle(double w, double h) : w_(w), h_(h) {}
    double area() const override { return w_ * h_; }
    std::string name() const override { return "Прямоугольник"; }
};
```

### Иерархия «Сотрудники»

```cpp
class Employee {
protected:
    std::string name_;
    double base_salary_;
public:
    Employee(std::string name, double base)
        : name_(std::move(name)), base_salary_(base) {}

    virtual ~Employee() = default;

    virtual double salary() const {
        return base_salary_;
    }

    std::string name() const { return name_; }
};

class Manager : public Employee {
    double bonus_;
public:
    Manager(std::string name, double base, double bonus)
        : Employee(std::move(name), base), bonus_(bonus) {}

    double salary() const override {
        return base_salary_ + bonus_;
    }
};
```

---

## 11. Частые ошибки

- **`private` поля родителя**, к которым обращается наследник — ошибка компиляции.
- **Забыли вызвать родительский конструктор** с параметрами — ошибка.
- **Не виртуальный деструктор** в полиморфной иерархии — утечка.
- **Переопределение без `virtual`** — не полиморфизм.
- **Наследование ради кода**, без «is-a» — плохой дизайн.
- **`override` без `virtual` в родителе** — ошибка компиляции.
- **Срезка объектов** (slicing) — копирование наследника в переменную
  родителя теряет часть.
- **`protected` поля** — компромисс; иногда лучше `private` + `protected`-методы.

---

## Примеры

- [inherit_basic.cpp](inherit_basic.cpp) — базовый класс + наследник
- [protected_access.cpp](protected_access.cpp) — уровни доступа
- [constructor_order.cpp](constructor_order.cpp) — порядок вызова
- [inherit_vs_compose.cpp](inherit_vs_compose.cpp) — «is-a» vs «has-a»
- [virtual_destructor.cpp](virtual_destructor.cpp) — виртуальный деструктор
- [employee_hierarchy.cpp](employee_hierarchy.cpp) — иерархия сотрудников

## Запуск

**CLion:** выбрать цель → **Shift+F10**.

**Терминал:**

```bash
mkdir build && cd build
cmake ..
cmake --build .
./lesson-21-inheritance-basic/inherit_basic
```

## Что дальше

Урок 22 — наследование: практика, RTTI, `static_cast` / `dynamic_cast`.