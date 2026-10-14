# Урок 12. Передача объектов в функции. Коллекции. Перегрузка операций

## Цель

Освоить работу с объектами в коллекциях, тонкости копирования и перемещения,
продвинутую перегрузку операторов и сортировку объектов.

## Ключевые понятия

- **Копирование объектов** — по значению, по ссылке, по константной ссылке.
- **Коллекция объектов** — `std::vector<T>`, `std::map<K, V>`.
- **Перегрузка операций** — `[]`, `()`, `->`, операторы сравнения.
- **Сортировка объектов** — через `operator<` или компаратор.
- **Правило нуля** — если не управляешь ресурсами, ничего не определяй.

---

## 1. Передача объектов

| Способ | Когда использовать |
|---|---|
| По значению `T obj` | если нужно скопировать или объект маленький |
| По ссылке `T& obj` | если нужно изменить |
| По константной ссылке `const T& obj` | если нужно только прочитать (по умолчанию) |
| По rvalue-ссылке `T&& obj` | для перемещения (урок 15) |

```cpp
void by_value(MyString s);            // копия
void by_ref(MyString& s);             // изменение
void by_cref(const MyString& s);      // чтение — основной способ
void by_rref(MyString&& s);           // перемещение
```

**Правило:** по умолчанию — `const&`. Меняешь — `&`. Копия — только
если действительно нужна.

---

## 2. Объекты в `std::vector`

```cpp
std::vector<Point> points;

points.push_back({1, 2});              // временный → перемещён
points.emplace_back(3, 4);             // создан на месте

for (const auto& p : points) {
    p.print();
}
```

**`push_back` vs `emplace_back`:**

- `push_back` принимает готовый объект.
- `emplace_back` принимает **аргументы конструктора** и создаёт
  объект прямо в контейнере — эффективнее.

```cpp
points.push_back(Point(5, 6));    // создать + переместить
points.emplace_back(5, 6);        // создать сразу на месте
```

**Обращение:**

```cpp
points[0].print();
points.front().print();
points.back().print();
points.at(1).print();    // с проверкой границ
```

**Удаление:**

```cpp
points.pop_back();                         // последний
points.erase(points.begin() + 2);          // по индексу
points.clear();                            // все
```

---

## 3. `std::vector` пользовательского класса

Важно: **`vector` копирует или перемещает элементы** при росте.
Если класс владеет ресурсами — нужен **копирующий или
перемещающий конструктор**.

```cpp
class MyString {
public:
    MyString(const char* s);
    MyString(const MyString& other);            // копирование
    MyString(MyString&& other) noexcept;        // перемещение
    ~MyString();
    // ...
};

std::vector<MyString> v;
v.push_back(MyString("a"));   // копирование или перемещение
```

**Подробно move-семантика — в уроке 15.**

---

## 4. Коллекция `std::map`

```cpp
#include <map>

std::map<std::string, int> ages;

ages["Иван"] = 25;
ages["Мария"] = 30;
ages.insert({"Пётр", 28});

for (const auto& [name, age] : ages) {    // C++17
    std::cout << name << ": " << age << "\n";
}

// Поиск
auto it = ages.find("Иван");
if (it != ages.end()) {
    std::cout << it->second << "\n";
}

// Или
if (ages.contains("Мария")) {              // C++20
    std::cout << ages["Мария"] << "\n";
}
```

**Ключи должны быть сравнимы** через `<`.

---

## 5. Перегрузка `[]`, `()`, `->`

### `operator[]` — доступ по индексу

```cpp
class MyArray {
private:
    std::vector<int> data_;

public:
    MyArray(std::size_t n) : data_(n, 0) {}

    int& operator[](std::size_t i) {
        return data_[i];               // для изменения
    }

    const int& operator[](std::size_t i) const {
        return data_[i];               // для чтения
    }
};

MyArray a(5);
a[0] = 10;
std::cout << a[0] << "\n";
```

**Две версии** — `const` и не-`const`. Иначе нельзя будет
читать из константного объекта.

### `operator()` — функтор

```cpp
class Adder {
private:
    int base_;
public:
    Adder(int b) : base_(b) {}

    int operator()(int x) const {
        return base_ + x;
    }
};

Adder add5(5);
std::cout << add5(10) << "\n";       // 15
```

Функторы — **объекты, которые можно «вызывать»**. Используются
в STL-алгоритмах.

### `operator->` — умный указатель

```cpp
class UniquePtr {
private:
    T* ptr_;
public:
    T* operator->() { return ptr_; }
    T& operator*() { return *ptr_; }
};
```

Подробно — в уроке 14.

---

## 6. Операторы сравнения

**Полный набор:**

```cpp
class Point {
public:
    int x, y;

    bool operator==(const Point& o) const { return x == o.x && y == o.y; }
    bool operator!=(const Point& o) const { return !(*this == o); }
    bool operator<(const Point& o)  const { return x < o.x || (x == o.x && y < o.y); }
    bool operator>(const Point& o)  const { return o < *this; }
    bool operator<=(const Point& o) const { return !(o < *this); }
    bool operator>=(const Point& o) const { return !(*this < o); }
};
```

**В C++20** — сокращённо через `operator<=>`:

```cpp
#include <compare>

class Point {
public:
    int x, y;

    auto operator<=>(const Point&) const = default;   // всё сразу
};
```

Компилятор сгенерирует `==`, `!=`, `<`, `>`, `<=`, `>=`.

---

## 7. Сортировка объектов

### Через `operator<`

```cpp
std::vector<Point> v = {{3, 1}, {1, 2}, {2, 3}};
std::sort(v.begin(), v.end());           // использует operator<
```

### Через компаратор

```cpp
std::sort(v.begin(), v.end(),
          [](const Point& a, const Point& b) {
              return a.y < b.y;          // по y
          });
```

### Через функцию

```cpp
bool by_length(const std::string& a, const std::string& b) {
    return a.size() < b.size();
}

std::sort(words.begin(), words.end(), by_length);
```

### Устойчивая сортировка

```cpp
std::stable_sort(v.begin(), v.end(), cmp);   // сохраняет порядок равных
```

### Частичная сортировка

```cpp
std::partial_sort(v.begin(), v.begin() + 3, v.end());   // топ-3
```

---

## 8. Свой «динамический массив» (учебный)

Упрощённая модель `std::vector` — для понимания, как оно устроено.

```cpp
template <typename T>
class MyVector {
private:
    T* data_ = nullptr;
    std::size_t size_ = 0;
    std::size_t capacity_ = 0;

public:
    MyVector() = default;

    ~MyVector() {
        delete[] data_;
    }

    void push_back(const T& value) {
        if (size_ == capacity_) {
            reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        }
        data_[size_++] = value;
    }

    void reserve(std::size_t new_cap) {
        if (new_cap <= capacity_) return;
        T* new_data = new T[new_cap];
        for (std::size_t i = 0; i < size_; ++i)
            new_data[i] = data_[i];
        delete[] data_;
        data_ = new_data;
        capacity_ = new_cap;
    }

    T& operator[](std::size_t i) { return data_[i]; }
    const T& operator[](std::size_t i) const { return data_[i]; }

    std::size_t size() const { return size_; }
    bool empty() const { return size_ == 0; }
};
```

**Что видно:**

- `new[]` / `delete[]`.
- Рост capacity **удвоением**.
- Перевыделение и копирование.
- `operator[]`.

**В реальном коде** — используйте `std::vector`.

---

## 9. Типичные задачи

### Список студентов с сортировкой

```cpp
struct Student {
    std::string name;
    double average;
};

std::vector<Student> students = {
    {"Иван", 4.5},
    {"Мария", 4.8},
    {"Пётр", 4.2}
};

std::sort(students.begin(), students.end(),
          [](const Student& a, const Student& b) {
              return a.average > b.average;
          });
```

### Словарь частот

```cpp
std::map<std::string, int> freq;
std::string word;
while (std::cin >> word) {
    ++freq[word];
}

for (const auto& [w, c] : freq) {
    std::cout << w << ": " << c << "\n";
}
```

### Многокритериальная сортировка

```cpp
std::sort(students.begin(), students.end(),
          [](const Student& a, const Student& b) {
              if (a.average != b.average) return a.average > b.average;
              return a.name < b.name;
          });
```

---

## 10. Частые ошибки

- **Копирование больших объектов** при передаче по значению — используйте `const&`.
- **Изменение `vector` внутри `for (const auto& x : v)`** — итераторы могут «поехать». Используйте индексы или пересобирайте.
- **`vector` объектов без копирующего или перемещающего конструктора** — ошибка компиляции.
- **`map[key]` создаёт элемент**, если его нет! Для проверки — `find` или `contains`.
- **Сравнение объектов без `operator<`** — `std::sort` не соберётся.
- **Компаратор не строгий** — если `cmp(a, a) == true` — UB.
- **Забыли `const` у компаратора** — не критично, но по стилю лучше.

---

## Примеры

- [objects_in_vector.cpp](objects_in_vector.cpp) — `vector` объектов, `emplace_back`
- [copy_semantics.cpp](copy_semantics.cpp) — копирование: значение, ссылка, const
- [operator_advanced.cpp](operator_advanced.cpp) — `[]`, `()`, `->`
- [custom_vector.cpp](custom_vector.cpp) — свой учебный `MyVector<T>`
- [sort_objects.cpp](sort_objects.cpp) — сортировка по разным критериям
- [comparison_operators.cpp](comparison_operators.cpp) — `==`, `<`, `<=>`

## Запуск

**CLion:** выбрать цель → **Shift+F10**.

**Терминал:**

```bash
mkdir build && cd build
cmake ..
cmake --build .
./lesson-12-objects-collections/objects_in_vector
```

## Что дальше

Урок 13 — исключения, RAII, правило трёх (пяти).