# Урок 25. Абстрактные классы, чистые виртуальные функции

## Цель

Освоить абстрактные классы — основу для иерархий, где базовый класс
задаёт контракт, а конкретные наследники его реализуют.

## Ключевые понятия

- **Чистая виртуальная функция** — `virtual ... = 0;` без тела.
- **Абстрактный класс** — содержит хотя бы одну чистую виртуальную функцию.
- **Нельзя создать объект** абстрактного класса.
- **Можно хранить указатель/ссылку** на абстрактный класс.
- **Контракт** — абстрактный класс говорит «что должно быть у наследников».
- **Интерфейс** — абстрактный класс без полей и без обычных методов.

---

## 1. Чистая виртуальная функция

```cpp
class Shape {
public:
    virtual double area() const = 0;    // ← = 0 делает функцию чистой
};
```

**Что это значит:**

- Функция **объявлена**, но **не имеет реализации**.
- Наследник **обязан** её переопределить.
- Иначе наследник тоже становится абстрактным.

**Синтаксис:**

```cpp
virtual ReturnType Name(params) = 0;
```

---

## 2. Абстрактный класс

Класс с хотя бы одной чистой виртуальной функцией — **абстрактный**.

**Нельзя создать объект:**

```cpp
Shape s;             // ошибка компиляции
Shape* p = new Shape; // тоже ошибка
```

**Можно:**

- Объявить указатель или ссылку.
- Хранить в них объекты **конкретных** наследников.
- Вызывать виртуальные методы — полиморфизм.

```cpp
Shape* p = new Circle(5);   // ок
p->area();                   // виртуальный вызов
```

---

## 3. Конкретный наследник

Наследник реализует **все** чистые виртуальные функции:

```cpp
class Circle : public Shape {
    double r_;
public:
    explicit Circle(double r) : r_(r) {}

    double area() const override {
        return 3.14159 * r_ * r_;
    }
};

Circle c(5);   // ок — конкретный класс
```

**Если наследник пропустит хотя бы одну** — тоже станет абстрактным.

```cpp
class HalfBaked : public Shape {
    // не реализован area
};

HalfBaked h;   // ошибка: HalfBaked абстрактный
```

---

## 4. Виртуальный деструктор в абстрактном классе

**Обязательно:**

```cpp
class Shape {
public:
    virtual ~Shape() = default;   // ← нужен!
    virtual double area() const = 0;
};
```

**Почему:** объекты наследников будут удаляться через базовый указатель.

```cpp
Shape* p = new Circle(5);
delete p;   // без virtual ~Shape — утечка
```

---

## 5. Абстрактный класс vs интерфейс

**Терминология:**

- **Абстрактный класс** — может иметь поля, обычные методы, конструкторы.
- **Интерфейс** — абстрактный класс **без полей** и **без обычных методов**,
  только чистые виртуальные.

```cpp
// Абстрактный класс с полем
class Animal {
protected:
    std::string name_;
public:
    explicit Animal(std::string n) : name_(std::move(n)) {}
    virtual ~Animal() = default;

    virtual std::string voice() const = 0;

    // Обычный метод — есть реализация
    void print() const {
        std::cout << name_ << ": " << voice() << "\n";
    }
};

// Интерфейс — только чистые виртуальные
class IPrintable {
public:
    virtual ~IPrintable() = default;
    virtual void print() const = 0;
};
```

**В C++ нет отдельного ключевого слова `interface`** — интерфейсы
делают через абстрактные классы.

---

## 6. Зачем абстрактные классы

**1. Контракт.** Базовый класс говорит: «у всех наследников будет `area()`».

**2. Полиморфизм.** `vector<unique_ptr<Shape>>` — работаем со всеми
единообразно.

**3. Запрет создания «неполного» объекта.** Нельзя создать `Shape` —
только конкретный `Circle` или `Square`.

**4. Расширяемость.** Новый наследник — просто реализует методы.
Остальной код **не меняется**.

**5. Разделение интерфейса и реализации.** Клиент работает с `Shape*`,
не знает о `Circle`.

---

## 7. Свойства абстрактного класса

**Что можно:**

- Поля (`protected` или `private`).
- Обычные виртуальные функции (с реализацией).
- Не виртуальные функции.
- Конструкторы и деструкторы.
- Статические методы.

**Что нельзя:**

- Создавать объект.
- Передавать по значению (срезка).

**Что нужно:**

- Виртуальный деструктор.
- Чистые виртуальные функции для обязательных методов.

---

## 8. Абстрактный класс с частичной реализацией

Не все методы обязаны быть чистыми. Некоторые могут иметь реализацию
по умолчанию.

```cpp
class Shape {
public:
    virtual ~Shape() = default;

    virtual double area() const = 0;                 // обязательный

    virtual std::string name() const {                // по умолчанию
        return "Фигура";
    }

    virtual void describe() const {                   // не чистая
        std::cout << name() << ": " << area() << "\n";
    }
};

class Circle : public Shape {
    double r_;
public:
    explicit Circle(double r) : r_(r) {}
    double area() const override { return 3.14159 * r_ * r_; }
    // name() не переопределяем — будет "Фигура"
};
```

**Правило:** делайте чистыми только **то, что обязательно**.

---

## 9. Типичные задачи

### Иерархия транспорта

```cpp
class Vehicle {
public:
    virtual ~Vehicle() = default;
    virtual int max_speed() const = 0;
    virtual std::string name() const = 0;

    void print() const {
        std::cout << name() << ": до " << max_speed() << " км/ч\n";
    }
};

class Car : public Vehicle {
public:
    int max_speed() const override { return 220; }
    std::string name() const override { return "Автомобиль"; }
};

class Bike : public Vehicle {
public:
    int max_speed() const override { return 40; }
    std::string name() const override { return "Велосипед"; }
};
```

### Иерархия сотрудников с абстрактным базовым

```cpp
class Employee {
protected:
    std::string name_;
public:
    explicit Employee(std::string name) : name_(std::move(name)) {}
    virtual ~Employee() = default;

    virtual double salary() const = 0;

    const std::string& name() const { return name_; }
};
```

### Плагины / обработчики

```cpp
class Handler {
public:
    virtual ~Handler() = default;
    virtual bool can_handle(const Request&) const = 0;
    virtual Response handle(const Request&) = 0;
};
```

Каждый конкретный `Handler` — своя логика. Основной код работает
с `vector<unique_ptr<Handler>>`.

---

## 10. Частые ошибки

- **Создание объекта абстрактного класса** — ошибка компиляции.
- **Забыли реализовать чистую виртуальную функцию** в наследнике —
  наследник тоже абстрактный.
- **Не виртуальный деструктор** — утечка при удалении через базу.
- **Передача по значению** — срезка (и ошибка компиляции).
- **`= 0` у функции с телом** — ошибка. Или `= 0`, или тело, не оба.
- **Чистая виртуальная функция вызвана из конструктора/деструктора** —
  UB.
- **Отсутствие `override`** — не ошибка, но легко промахнуться
  с сигнатурой.

---

## Примеры

- [abstract_basic.cpp](abstract_basic.cpp) — простой абстрактный класс
- [pure_virtual.cpp](pure_virtual.cpp) — чистые виртуальные функции
- [abstract_hierarchy.cpp](abstract_hierarchy.cpp) — иерархия фигур
- [abstract_vs_concrete.cpp](abstract_vs_concrete.cpp) — абстрактный vs конкретный
- [interface_demo.cpp](interface_demo.cpp) — интерфейсы через абстрактные классы
- [abstract_factory.cpp](abstract_factory.cpp) — фабрика объектов

## Запуск

**CLion:** выбрать цель → **Shift+F10**.

**Терминал:**

```bash
mkdir build && cd build
cmake ..
cmake --build .
./lesson-25-abstract-classes/abstract_basic
```

## Что дальше

Урок 26 — абстрактные классы: практика, интерфейсы.