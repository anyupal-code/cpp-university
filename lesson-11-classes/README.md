# Урок 11. Классы: конструкторы, деструкторы, перегрузка операций

## Цель

Освоить классы — основу ООП: конструкторы, деструкторы, копирование,
перегрузку операторов и правило трёх.

## Ключевые понятия

- **Класс** — пользовательский тип с данными и методами.
- **Объект** — экземпляр класса.
- **Конструктор** — вызывается при создании объекта.
- **Деструктор** — вызывается при уничтожении объекта.
- **`this`** — указатель на текущий объект.
- **Перегрузка операторов** — свои действия для `+`, `==`, `<<` и т.д.
- **Правило трёх** — если нужен свой деструктор, копирование или
  присваивание — нужны все три.

---

## 1. `struct` vs `class`

| Свойство | `struct` | `class` |
|---|---|---|
| Доступ по умолчанию | `public` | `private` |
| Наследование по умолчанию | `public` | `private` |

**Всё остальное — одинаково.** Разница только в стиле:

- `struct` — для простых данных.
- `class` — для полноценных объектов с инкапсуляцией.

---

## 2. Простой класс

```cpp
class Point {
private:
    int x_;
    int y_;

public:
    // Конструктор
    Point(int x, int y) : x_(x), y_(y) {}

    // Методы
    int get_x() const { return x_; }
    int get_y() const { return y_; }

    void move(int dx, int dy) {
        x_ += dx;
        y_ += dy;
    }

    void print() const {
        std::cout << "(" << x_ << ", " << y_ << ")\n";
    }
};
```

**Соглашение об именах:**

- Приватные поля — `x_`, `y_` или `m_x`, `m_y`.
- Публичные методы — `get_x()`, `set_x()`, `move()`.

**Разделы доступа:**

- `private:` — только внутри класса.
- `public:` — везде.
- `protected:` — для наследников (урок 21).

---

## 3. Конструкторы

**Конструктор** вызывается при создании объекта.

### Конструктор по умолчанию

```cpp
class Point {
public:
    Point() : x_(0), y_(0) {}
private:
    int x_, y_;
};
```

### Конструктор с параметрами

```cpp
Point(int x, int y) : x_(x), y_(y) {}
```

**Список инициализации** `: x_(x), y_(y)`:

- Инициализирует поля **до** тела конструктора.
- **Эффективнее** присваивания в теле.
- **Обязателен** для `const`-полей и ссылок.

### Делегирующий конструктор (C++11)

```cpp
Point() : Point(0, 0) {}
Point(int x, int y) : x_(x), y_(y) {}
```

### `explicit`

Запрещает неявное преобразование:

```cpp
explicit Point(int x) : x_(x), y_(0) {}

Point p = 5;      // ошибка без explicit
Point p(5);       // ок
```

**Правило:** конструкторы с одним параметром — помечайте `explicit`,
если неявное преобразование не нужно.

---

## 4. Деструктор

**Деструктор** вызывается при уничтожении объекта.

```cpp
class Resource {
public:
    Resource() {
        data_ = new int[100];
        std::cout << "Ресурс создан\n";
    }

    ~Resource() {
        delete[] data_;
        std::cout << "Ресурс уничтожен\n";
    }

private:
    int* data_;
};
```

**Когда вызывается:**

- выход из области видимости,
- `delete` для объекта на куче,
- при завершении программы (для глобальных).

**Зачем:**

- освободить память (`delete`, `delete[]`),
- закрыть файлы,
- освободить другие ресурсы.

**Правило RAII:** ресурс захвачен в конструкторе — освобождён
в деструкторе. Деструктор **никогда не бросает исключения**.

---

## 5. `this`

**`this`** — указатель на текущий объект.

```cpp
class Point {
public:
    Point& set_x(int x) {
        this->x_ = x;
        return *this;    // для цепочек вызовов
    }
private:
    int x_;
};

p.set_x(5).set_x(10);   // цепочка
```

**`this` нужен, когда:**

- поле и параметр совпадают по имени (`x_` и `x` — разные, `this` не обязателен),
- возвращаем ссылку на себя,
- передаём себя в другую функцию.

---

## 6. Перегрузка операторов

Операторы можно определять для своих типов.

### Бинарные: `+`, `-`, `*`

```cpp
class Vector2 {
public:
    double x, y;

    Vector2(double x, double y) : x(x), y(y) {}

    Vector2 operator+(const Vector2& other) const {
        return {x + other.x, y + other.y};
    }

    Vector2 operator-(const Vector2& other) const {
        return {x - other.x, y - other.y};
    }

    Vector2 operator*(double k) const {
        return {x * k, y * k};
    }
};
```

### Сравнение: `==`, `!=`

```cpp
bool operator==(const Vector2& other) const {
    return x == other.x && y == other.y;
}

bool operator!=(const Vector2& other) const {
    return !(*this == other);
}
```

**В C++20** достаточно определить `operator==`, а `!=` компилятор
сгенерирует сам. Ещё — **`operator<=>`** (three-way comparison).

### Вывод: `operator<<`

```cpp
std::ostream& operator<<(std::ostream& os, const Vector2& v) {
    os << "(" << v.x << ", " << v.y << ")";
    return os;
}

std::cout << v << "\n";
```

**Вне класса**, потому что левый операнд — `std::ostream`.

### Инкремент: `++`

```cpp
Vector2& operator++() {          // префиксный
    ++x; ++y;
    return *this;
}

Vector2 operator++(int) {        // постфиксный (int — фиктивный)
    Vector2 old = *this;
    ++(*this);
    return old;
}
```

---

## 7. Копирование

### Конструктор копирования

```cpp
class MyString {
public:
    MyString(const char* s) {
        size_ = std::strlen(s);
        data_ = new char[size_ + 1];
        std::strcpy(data_, s);
    }

    // Копирующий конструктор
    MyString(const MyString& other) {
        size_ = other.size_;
        data_ = new char[size_ + 1];
        std::strcpy(data_, other.data_);
    }

    ~MyString() { delete[] data_; }

private:
    char* data_;
    std::size_t size_;
};
```

**Вызывается:**

- `MyString b = a;`
- передача по значению,
- возврат по значению.

### Оператор присваивания

```cpp
MyString& operator=(const MyString& other) {
    if (this == &other) return *this;   // самоприсваивание

    delete[] data_;                     // освободить старое
    size_ = other.size_;
    data_ = new char[size_ + 1];
    std::strcpy(data_, other.data_);
    return *this;
}
```

**Правила:**

1. Проверить самоприсваивание (`this == &other`).
2. Освободить старые ресурсы.
3. Скопировать новые.
4. Вернуть `*this`.

---

## 8. Правило трёх / пяти

**Правило трёх (C++03):** если класс определяет **хотя бы одно** из:

1. деструктор,
2. копирующий конструктор,
3. копирующее присваивание,

— то, скорее всего, нужно определить **все три**.

**Правило пяти (C++11):** добавляются **перемещающие** операции:

4. move-конструктор,
5. move-присваивание.

**Move-семантика — в уроке 15.**

**Если класс не управляет ресурсами напрямую** — правило не нужно,
компилятор сгенерирует всё сам.

---

## 9. `= default` и `= delete`

**C++11:**

```cpp
class Point {
public:
    Point() = default;                    // сгенерировать
    Point(const Point&) = default;

    Point& operator=(const Point&) = delete;   // запретить
};
```

- **`= default`** — «сгенерируй стандартную версию».
- **`= delete`** — «запрети эту операцию».

**Пример:** запретить копирование:

```cpp
class NonCopyable {
public:
    NonCopyable() = default;
    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;
};
```

---

## 10. Типичные задачи

### Класс «Дробь»

```cpp
class Fraction {
private:
    int num_, den_;

    void reduce() {
        int g = std::gcd(num_, den_);
        num_ /= g;
        den_ /= g;
    }

public:
    Fraction(int n, int d) : num_(n), den_(d) {
        if (d == 0) throw std::invalid_argument("den = 0");
        reduce();
    }

    Fraction operator+(const Fraction& o) const {
        return {num_ * o.den_ + o.num_ * den_, den_ * o.den_};
    }

    double value() const {
        return static_cast<double>(num_) / den_;
    }

    friend std::ostream& operator<<(std::ostream&, const Fraction&);
};
```

### Класс «Вектор 2D»

```cpp
class Vector2 {
public:
    double x, y;

    Vector2(double x, double y) : x(x), y(y) {}

    Vector2 operator+(const Vector2& o) const {
        return {x + o.x, y + o.y};
    }

    double length() const {
        return std::sqrt(x * x + y * y);
    }

    bool operator==(const Vector2& o) const {
        return x == o.x && y == o.y;
    }
};
```

---

## 11. Частые ошибки

- **Забыли `;` после `}` класса.**
- **Поля `public` без необходимости** — нарушение инкапсуляции.
- **Присваивание вместо списка инициализации** — менее эффективно.
- **Деструктор не освобождает ресурсы** — утечка.
- **Копирование без глубокого копирования** — двойное `delete`.
- **Самоприсваивание без проверки** — `delete` себя же.
- **Оператор возвращает по значению, а не по ссылке** — лишние копии.
- **Деструктор бросает исключение** — UB.

---

## Примеры

- [class_basic.cpp](class_basic.cpp) — простой класс, `public` / `private`
- [constructors.cpp](constructors.cpp) — конструкторы, `explicit`, делегирование
- [destructor.cpp](destructor.cpp) — деструктор, RAII
- [operator_overload.cpp](operator_overload.cpp) — `+`, `==`, `<<`, `++`
- [copy_ctor.cpp](copy_ctor.cpp) — копирующий конструктор
- [rule_of_three.cpp](rule_of_three.cpp) — правило трёх в действии

## Запуск

**CLion:** выбрать цель → **Shift+F10**.

**Терминал:**

```bash
mkdir build && cd build
cmake ..
cmake --build .
./lesson-11-classes/class_basic
```

## Что дальше

Урок 12 — передача объектов в функции, коллекции, перегрузка операций.