# Урок 14. Умные указатели: `unique_ptr`, `shared_ptr`, `weak_ptr`

## Цель

Освоить умные указатели — основной инструмент управления памятью
в современном C++. Раз и навсегда забыть про `new` / `delete`.

## Ключевые понятия

- **`std::unique_ptr`** — единственный владелец.
- **`std::shared_ptr`** — общий владелец, счётчик ссылок.
- **`std::weak_ptr`** — слабая ссылка, не владеет.
- **`std::make_unique` / `std::make_shared`** — фабрики.
- **Циклическая ссылка** — утечка в `shared_ptr`.
- **Правило нуля** — если не пишешь свой ресурс, ничего не определяй.

---

## 1. Зачем умные указатели

**Старый код:**

```cpp
int* p = new int(42);
// ... 100 строк ...
delete p;   // если забыли — утечка
// если брошено исключение до delete — тоже утечка
```

**С умными указателями:**

```cpp
auto p = std::make_unique<int>(42);
// всё освободится автоматически при выходе из области видимости
```

**RAII:** владение — часть объекта. Память освобождается
в деструкторе. Исключения тоже не проблема.

---

## 2. `std::unique_ptr` — единственный владелец

- Нельзя копировать.
- Можно **перемещать** (`std::move`).
- Классический способ владения динамическим объектом.

### Создание

```cpp
#include <memory>

// Предпочтительно
auto p1 = std::make_unique<int>(42);

// Прямое создание
std::unique_ptr<int> p2(new int(42));
```

**`make_unique`** — безопаснее и короче. Рекомендуется.

### Использование

```cpp
auto p = std::make_unique<int>(42);

std::cout << *p << "\n";       // 42
*p = 100;
std::cout << *p << "\n";       // 100
```

### Нельзя копировать

```cpp
auto a = std::make_unique<int>(42);
// auto b = a;              // ошибка
auto b = std::move(a);       // ок: перемещение владения
// теперь a == nullptr
```

### Проверка

```cpp
if (p) {
    std::cout << *p << "\n";
}

if (p == nullptr) {
    std::cout << "пустой\n";
}
```

### Сброс

```cpp
p.reset();                   // освободить
p.reset(new int(100));       // заменить
int* raw = p.release();      // отпустить владение (редко нужно)
```

### Массивы

```cpp
auto arr = std::make_unique<int[]>(10);
for (int i = 0; i < 10; ++i)
    arr[i] = i * i;
```

---

## 3. `unique_ptr` и полиморфизм

```cpp
class Shape {
public:
    virtual ~Shape() = default;
    virtual double area() const = 0;
};

class Circle : public Shape {
    double r_;
public:
    Circle(double r) : r_(r) {}
    double area() const override { return 3.14159 * r_ * r_; }
};

class Rect : public Shape {
    double w_, h_;
public:
    Rect(double w, double h) : w_(w), h_(h) {}
    double area() const override { return w_ * h_; }
};

std::vector<std::unique_ptr<Shape>> shapes;
shapes.push_back(std::make_unique<Circle>(5));
shapes.push_back(std::make_unique<Rect>(3, 4));

for (const auto& s : shapes) {
    std::cout << s->area() << "\n";   // виртуальный вызов
}
```

- **Виртуальный деструктор обязателен** в базовом классе.
- `unique_ptr` корректно удаляет объект **через базовый указатель**.

---

## 4. `std::shared_ptr` — общий владелец

- Счётчик ссылок: сколько `shared_ptr` указывают на объект.
- Объект удаляется, когда счётчик = 0.
- **Копируется** (увеличивает счётчик).

### Создание

```cpp
auto p1 = std::make_shared<int>(42);

std::shared_ptr<int> p2(new int(42));   // реже
```

**`make_shared`** эффективнее: выделяет память **одним** блоком
под объект и счётчик.

### Использование

```cpp
auto a = std::make_shared<int>(42);
std::cout << *a << "\n";               // 42
std::cout << a.use_count() << "\n";    // 1

auto b = a;                            // копия — владение общее
std::cout << a.use_count() << "\n";    // 2

b.reset();
std::cout << a.use_count() << "\n";    // 1

a.reset();
std::cout << a.use_count() << "\n";    // 0
// объект уничтожен
```

### Когда использовать

- **Несколько владельцев** одного объекта.
- Разделяемое состояние между компонентами.
- Кэши, графы, общие ресурсы.

**Осторожно:** `shared_ptr` **дороже** `unique_ptr` — атомарный счётчик.
Без необходимости не используйте.

---

## 5. `std::weak_ptr` — слабая ссылка

- **Не увеличивает** счётчик ссылок.
- Используется для **наблюдения** за объектом, которым владеет
  кто-то другой.
- Для доступа — `lock()`.

```cpp
auto sp = std::make_shared<int>(42);
std::weak_ptr<int> wp = sp;

std::cout << sp.use_count() << "\n";   // 1 (wp не считается)

if (auto locked = wp.lock()) {
    std::cout << *locked << "\n";      // 42
} else {
    std::cout << "объект уничтожен\n";
}

sp.reset();

std::cout << wp.expired() << "\n";     // 1 (true)
```

**Зачем:**

- **Разорвать циклические ссылки.**
- Наблюдать за объектом, не продлевая ему жизнь.
- Кэш с проверкой живости.

---

## 6. Циклические ссылки — главная проблема `shared_ptr`

```cpp
struct Node {
    std::shared_ptr<Node> next;
    std::shared_ptr<Node> prev;
};

auto a = std::make_shared<Node>();
auto b = std::make_shared<Node>();

a->next = b;
b->prev = a;
```

**Что произойдёт:** `use_count` у `a` и `b` **никогда не станет 0**.
Объекты не освободятся → **утечка**.

**Решение:** одна из ссылок должна быть `weak_ptr`.

```cpp
struct Node {
    std::shared_ptr<Node> next;
    std::weak_ptr<Node> prev;   // ← слабая ссылка
};
```

Теперь цикл разорван, и объекты корректно удаляются.

---

## 7. Умные указатели в контейнерах

### `vector<unique_ptr<T>>`

```cpp
std::vector<std::unique_ptr<Shape>> shapes;

shapes.push_back(std::make_unique<Circle>(5));
shapes.push_back(std::make_unique<Rect>(3, 4));

for (const auto& s : shapes) {
    std::cout << s->area() << "\n";
}
```

- `vector` хранит **владельцев**.
- **Копирование невозможно** — только перемещение.
- **Идеально** для полиморфных коллекций.

### `vector<shared_ptr<T>>`

```cpp
std::vector<std::shared_ptr<Shape>> shapes;

auto c = std::make_shared<Circle>(5);
shapes.push_back(c);
shapes.push_back(c);   // один объект в двух слотах

std::cout << c.use_count() << "\n";   // 3 (c + два в vector)
```

---

## 8. Передача владения в функции

### `unique_ptr` — по значению (передача владения)

```cpp
void consume(std::unique_ptr<Shape> s) {
    // теперь функция владеет объектом
    // уничтожится при выходе
}

auto p = std::make_unique<Circle>(5);
consume(std::move(p));   // владение перешло
// p == nullptr
```

### `unique_ptr` — по ссылке (без передачи владения)

```cpp
void use(const std::unique_ptr<Shape>& s) {
    std::cout << s->area() << "\n";
}

auto p = std::make_unique<Circle>(5);
use(p);                  // p сохраняет владение
```

### `shared_ptr` — по значению (разделение владения)

```cpp
void share(std::shared_ptr<Shape> s) {
    // s — ещё один владелец
}

auto p = std::make_shared<Circle>(5);
share(p);                // use_count вырос
```

### `shared_ptr` — по константной ссылке (без копии)

```cpp
void use(const std::shared_ptr<Shape>& s) {
    std::cout << s->area() << "\n";
}
```

**Правило:**

| Хотим | Как передать |
|---|---|
| передать владение | `unique_ptr<T>` по значению |
| сохранить владение, только использовать | `const unique_ptr<T>&` |
| разделить владение | `shared_ptr<T>` по значению |
| использовать, не разделяя | `const shared_ptr<T>&` |
| вообще без владения | `T&` или `T*` |

---

## 9. Когда что использовать

| Ситуация | Инструмент |
|---|---|
| Один владелец | `unique_ptr` |
| Несколько владельцев | `shared_ptr` |
| Наблюдение без владения | `weak_ptr` |
| Не владеет, просто смотрит | `T*` или `T&` |
| Массив объектов | `std::vector<T>` |
| Строка | `std::string` |

**Правило нуля:** по умолчанию — **стек** или `vector`.
Указатели — когда объект должен жить **дольше** или **разделяться**.

---

## 10. Частые ошибки

- **`shared_ptr` там, где хватит `unique_ptr`** — лишний оверхед.
- **Циклические ссылки в `shared_ptr`** — утечка. Ломайте `weak_ptr`.
- **`std::shared_ptr<T>(new T)` дважды для одного объекта** — два разных
  счётчика, двойное удаление. Используйте `make_shared`.
- **Отсутствие виртуального деструктора** в базовом классе —
  `delete` через базовый указатель → UB.
- **`unique_ptr` без `std::move`** — ошибка компиляции.
- **Хранить `weak_ptr` после `shared_ptr.reset()`** — объект мёртв,
  `lock()` вернёт `nullptr`.
- **Разыменование пустого `unique_ptr`** — UB.
- **Возврат `unique_ptr` из функции** — работает, `move` неявно.

---

## 11. Типичные задачи

### Фабрика объектов

```cpp
std::unique_ptr<Shape> make_shape(int type) {
    if (type == 1) return std::make_unique<Circle>(5);
    if (type == 2) return std::make_unique<Rect>(3, 4);
    return nullptr;
}
```

### Разделяемый кэш

```cpp
std::unordered_map<std::string, std::shared_ptr<Cache>> cache;

auto& entry = cache[key];
if (!entry) {
    entry = std::make_shared<Cache>(load(key));
}
return entry;
```

### Наблюдение без владения

```cpp
class Observer {
    std::weak_ptr<Subject> subject_;
public:
    explicit Observer(std::weak_ptr<Subject> s) : subject_(s) {}

    void on_event() {
        if (auto s = subject_.lock()) {
            s->notify();
        }
    }
};
```

---

## Примеры

- [unique_basic.cpp](unique_basic.cpp) — `unique_ptr`, `make_unique`, `move`
- [unique_polymorphism.cpp](unique_polymorphism.cpp) — `unique_ptr` с полиморфизмом
- [shared_basic.cpp](shared_basic.cpp) — `shared_ptr`, `use_count`
- [shared_cycle.cpp](shared_cycle.cpp) — цикл и его разрыв через `weak_ptr`
- [weak_demo.cpp](weak_demo.cpp) — `weak_ptr`, `lock`, `expired`
- [smart_in_container.cpp](smart_in_container.cpp) — умные указатели в `vector`

## Запуск

**CLion:** выбрать цель → **Shift+F10**.

**Терминал:**

```bash
mkdir build && cd build
cmake ..
cmake --build .
./lesson-14-smart-pointers/unique_basic
```

## Что дальше

Урок 15 — move-семантика, `std::move`, rvalue-ссылки.