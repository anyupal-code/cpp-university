# Урок 15. Move-семантика. `std::move`, rvalue-ссылки

## Цель

Понять, как избежать лишнего копирования, освоить move-семантику
и rvalue-ссылки — ключевую возможность C++11.

## Ключевые понятия

- **lvalue** — именованное значение (`x`, `arr[0]`).
- **rvalue** — временное значение (`5`, `x + y`, возврат функции).
- **rvalue-ссылка `T&&`** — ссылка на временный объект.
- **Move-конструктор** — «украсть» ресурсы у rvalue вместо копирования.
- **`std::move`** — превратить lvalue в rvalue (разрешить перемещение).
- **`std::forward`** — perfect forwarding в шаблонах.
- **Copy elision** — когда даже move не вызывается.

---

## 1. lvalue и rvalue

**lvalue** — то, что имеет **имя** и адрес:

```cpp
int x = 5;        // x — lvalue
x = 10;           // можно присвоить
int* p = &x;      // можно взять адрес
```

**rvalue** — временное значение, имени нет:

```cpp
5                 // rvalue
x + y             // rvalue
foo()             // rvalue (если возвращает по значению)
std::string("hi") // rvalue
```

**Ключевое отличие:**

- У lvalue можно взять адрес.
- lvalue живёт «долго» (по крайней мере, до конца области видимости).
- rvalue исчезает сразу после использования.

---

## 2. rvalue-ссылки `T&&`

**Ссылка на временный объект.** Появилась в C++11.

```cpp
int&& r = 5;      // rvalue-ссылка
r = 10;           // можно менять (r — уже lvalue)

// int&& r2 = x;   // ошибка: x — lvalue
```

**Связывание:**

| Ссылка | Может связаться с |
|---|---|
| `T&` (lvalue-ссылка) | только lvalue |
| `const T&` | lvalue и rvalue |
| `T&&` (rvalue-ссылка) | только rvalue |

**Зачем:** перегрузка функций по категории значения.

```cpp
void f(int& x)  { std::cout << "lvalue\n"; }
void f(int&& x) { std::cout << "rvalue\n"; }

int a = 5;
f(a);             // lvalue
f(5);             // rvalue
f(a + 1);         // rvalue
f(std::move(a));  // rvalue
```

---

## 3. Move-конструктор

**Проблема.** Копирование больших объектов дорого:

```cpp
std::vector<int> a(1'000'000);
std::vector<int> b = a;   // копирование 4 МБ
```

Но если `a` больше не нужен — можно **«украсть»** данные.

**Move-конструктор** забирает ресурсы у rvalue:

```cpp
class Buffer {
private:
    int* data_;
    std::size_t size_;

public:
    // Обычный конструктор
    Buffer(std::size_t n) : data_(new int[n]), size_(n) {}

    // Копирующий конструктор — копирует данные
    Buffer(const Buffer& o)
        : data_(new int[o.size_]), size_(o.size_) {
        std::copy(o.data_, o.data_ + size_, data_);
    }

    // Move-конструктор — забирает данные, не копирует
    Buffer(Buffer&& o) noexcept
        : data_(o.data_), size_(o.size_) {
        o.data_ = nullptr;
        o.size_ = 0;
    }

    ~Buffer() { delete[] data_; }

    std::size_t size() const { return size_; }
};
```

**Что происходит:**

1. `data_` забирает указатель у `o`.
2. `o` обнуляется — теперь «пустой».
3. Никакого копирования — только передача указателя.

**`noexcept`** — критично. `std::vector` использует move только
если move-конструктор `noexcept`, иначе копирует для гарантии
безопасности исключений.

---

## 4. Move-присваивание

```cpp
Buffer& operator=(Buffer&& o) noexcept {
    if (this != &o) {
        delete[] data_;           // освободить старые данные
        data_ = o.data_;          // забрать у o
        size_ = o.size_;
        o.data_ = nullptr;
        o.size_ = 0;
    }
    return *this;
}
```

**Порядок:**

1. Проверка самоприсваивания.
2. Освобождение своих ресурсов.
3. Присваивание ресурсов от `o`.
4. Обнуление `o`.

---

## 5. `std::move`

**Не двигает.** Просто **приводит lvalue к rvalue-ссылке** —
разрешает move.

```cpp
#include <utility>

std::string a = "Hello";
std::string b = std::move(a);   // вызовет move-конструктор

std::cout << a << "\n";         // a пустая (перемещена)
std::cout << b << "\n";         // "Hello"
```

**Что делает `std::move`:**

```cpp
// Внутри:
template <typename T>
constexpr std::remove_reference_t<T>&& move(T&& t) noexcept {
    return static_cast<std::remove_reference_t<T>&&>(t);
}
```

Это **просто каст**. Ничего не двигает.

**После `std::move(x)` объект `x` — в «перемещённом состоянии».**
Читать — можно (но не гарантируется осмысленное значение),
использовать — с осторожностью. Обнулять — обычно не нужно.

**Не пишите `std::move` в `return`** локальной переменной:

```cpp
// Плохо:
return std::move(local);

// Хорошо:
return local;   // компилятор сам применит move или NRVO
```

Правило: `std::move` — **последнее** использование объекта.

---

## 6. `noexcept` и `std::vector`

**Ключевой момент:** `std::vector` при росте выбирает
между копированием и перемещением.

```cpp
std::vector<Buffer> v;
v.push_back(Buffer(100));    // создан временный, потом «перемещён»
```

**Правило:** если move-конструктор объявлен `noexcept` — `vector`
перемещает. Иначе — копирует (для «строгой гарантии исключений»).

**Всегда** помечайте move-операции `noexcept`.

---

## 7. `std::forward` — perfect forwarding

В шаблонах нужно «пробросить» аргумент **с сохранением категории**.

```cpp
template <typename T>
void wrapper(T&& arg) {
    // arg — lvalue, но мы хотим передать дальше
    // как есть: lvalue — lvalue, rvalue — rvalue
    target(std::forward<T>(arg));
}
```

**Правила:**

- В шаблоне `T&&` — **forwarding reference** (не обычная rvalue-ссылка).
- `std::forward<T>` — сохраняет категорию аргумента.
- `std::move` — **всегда** делает rvalue. `std::forward` — только если
  так и было.

**Пример:**

```cpp
template <typename T>
void log_and_call(T&& arg) {
    std::cout << "Вызов с аргументом\n";
    some_function(std::forward<T>(arg));
}

std::string s = "hello";
log_and_call(s);           // lvalue -> lvalue
log_and_call("world");     // rvalue -> rvalue
```

**Perfect forwarding** используется в:

- `std::make_unique`, `std::make_shared`,
- `std::vector::emplace_back`,
- любых фабриках и обёртках.

---

## 8. Copy elision (C++17)

**Компилятор может не вызывать ни copy, ни move**, если объект
создаётся сразу «на месте».

```cpp
Buffer make() {
    return Buffer(100);
}

Buffer b = make();   // ни copy, ни move — объект создан на месте b
```

**C++17:** в некоторых случаях **гарантированно** без копирования.
Компилятор строит объект прямо на месте вызова.

**Следствие:** `Buffer(Buffer&&)` может вообще не вызываться.
Но он **должен быть определён**, если класс с пользовательским
деструктором.

---

## 9. Правило пяти — полный вид

Если класс управляет ресурсами:

```cpp
class Buffer {
public:
    // 1. Конструктор
    explicit Buffer(std::size_t n);

    // 2. Деструктор
    ~Buffer();

    // 3. Копирующий конструктор
    Buffer(const Buffer& o);

    // 4. Копирующее присваивание
    Buffer& operator=(const Buffer& o);

    // 5. Move-конструктор
    Buffer(Buffer&& o) noexcept;

    // 6. Move-присваивание
    Buffer& operator=(Buffer&& o) noexcept;
};
```

**Правило нуля:** предпочтительнее **не управлять ресурсами вручную**.
Используйте `vector`, `string`, `unique_ptr` — и move-семантика
работает «из коробки».

---

## 10. Типичные задачи

### Функция принимает rvalue — забирает владение

```cpp
void consume(std::vector<int>&& v) {
    std::vector<int> local = std::move(v);
    // ...
}

consume(std::vector<int>(1'000'000));  // без копирования
```

### Функция возвращает большой объект

```cpp
std::vector<int> make_big() {
    std::vector<int> v(1'000'000);
    return v;   // NRVO — без копирования
}
```

### `emplace_back` vs `push_back`

```cpp
std::vector<Buffer> v;

// push_back с временным — move:
v.push_back(Buffer(100));

// emplace_back — создание на месте:
v.emplace_back(100);

// Без разницы по производительности для простых типов,
// но emplace может быть эффективнее для сложных.
```

### Класс с `unique_ptr` — move-only

```cpp
class Holder {
private:
    std::unique_ptr<int> data_;
public:
    explicit Holder(int x) : data_(std::make_unique<int>(x)) {}

    // Move-only: copy запрещён
    Holder(const Holder&) = delete;
    Holder& operator=(const Holder&) = delete;

    Holder(Holder&&) = default;
    Holder& operator=(Holder&&) = default;
};
```

---

## 11. Частые ошибки

- **Использовать объект после `std::move`** — неопределённое состояние.
- **`std::move` в `return`** — мешает NRVO, компилятор сам применит.
- **Move-операции без `noexcept`** — `vector` будет копировать.
- **Путать `std::move` и `std::forward`** — move всегда rvalue,
  forward сохраняет категорию.
- **`std::move` для const-объекта** — «двигает» как копирование
  (const rvalue-ссылка не привязывается к move).
- **Move-конструктор не обнуляет источник** — возможен двойный `delete`.
- **Возврат ссылки на перемещённый объект** — UB.

---

## Примеры

- [lvalue_rvalue.cpp](lvalue_rvalue.cpp) — категории значений
- [rvalue_refs.cpp](rvalue_refs.cpp) — `T&&`, привязка, перегрузка
- [move_ctor.cpp](move_ctor.cpp) — move-конструктор vs copy
- [move_assign.cpp](move_assign.cpp) — move-присваивание
- [std_move.cpp](std_move.cpp) — `std::move` в действии
- [perfect_forward.cpp](perfect_forward.cpp) — `std::forward`, шаблоны

## Запуск

**CLion:** выбрать цель → **Shift+F10**.

**Терминал:**

```bash
mkdir build && cd build
cmake ..
cmake --build .
./lesson-15-move-semantics/lvalue_rvalue
```

## Что дальше

**Модуль 1 завершён.** Дальше — **Модуль 2: STL и продвинутые темы**:

- Урок 16 — контейнеры последовательные: `vector`, `deque`, `list`.
- Урок 17 — контейнеры: практика.
- Урок 18 — ассоциативные: `map`, `set`, `unordered_map`.
- Урок 19 — алгоритмы STL: `sort`, `find`, ranges, лямбды.
- Урок 20 — разбор демо КР.
- Урок 21–28 — ООП-продвинутый: наследование, RTTI, абстрактные классы.