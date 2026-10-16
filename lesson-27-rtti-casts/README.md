# Урок 27. RTTI, виды кастов: полная картина

## Цель

Систематизировать все виды приведения типов в C++ и RTTI.
Понять, когда какой каст использовать.

## Ключевые понятия

- **`static_cast`** — проверка на этапе компиляции.
- **`dynamic_cast`** — проверка во время выполнения (нужен `virtual`).
- **`const_cast`** — снятие `const` (осторожно!).
- **`reinterpret_cast`** — переинтерпретация битов (опасно).
- **C-style cast** — `(T)x` — не используйте.
- **RTTI** — информация о типе во время выполнения.
- **`typeid`, `type_info`** — механизмы RTTI.

---

## 1. Обзор: четыре каста

| Каст | Когда использовать |
|---|---|
| `static_cast<T>(x)` | известное преобразование на этапе компиляции |
| `dynamic_cast<T>(x)` | приведение вниз по иерархии с проверкой |
| `const_cast<T>(x)` | снятие `const`/`volatile` |
| `reinterpret_cast<T>(x)` | переинтерпретация битов (низкий уровень) |

**Никогда:** C-style `(T)x` — может делать всё сразу, непонятно, что именно.

**Правило:** используй **самый узкий** каст из подходящих.

---

## 2. `static_cast`

**Проверка на этапе компиляции.** Компилятор доверяет тебе.

**Где применять:**

- Числовые преобразования: `double` → `int`.
- `void*` → `T*` (если знаешь, что там `T*`).
- Вверх по иерархии (Derived → Base) — безопасно.
- Явный вызов конструктора или оператора преобразования.

```cpp
double d = 3.14;
int i = static_cast<int>(d);          // 3

Base* b = static_cast<Base*>(derived_ptr);   // вверх — безопасно

Derived* d2 = static_cast<Derived*>(base_ptr);  // вниз — БЕЗ проверки
// если base_ptr не указывает на Derived — UB
```

**Что НЕ может:**

- Снять `const`.
- Переинтерпретировать биты.
- Проверить тип во время выполнения.

---

## 3. `dynamic_cast`

**Проверка во время выполнения.** Требует **виртуальных функций**
в базовом классе.

```cpp
Base* b = get_some_object();

if (auto* d = dynamic_cast<Derived*>(b)) {
    d->derived_method();
} else {
    // не Derived
}
```

**Для ссылок** — исключение при неудаче:

```cpp
try {
    Derived& d = dynamic_cast<Derived&>(*b);
} catch (const std::bad_cast&) {
    // не Derived
}
```

**Что умеет:**

- Приведение **вниз** (Base → Derived).
- Приведение **вбок** (между сиблингами — редко).
- Работает только для **полиморфных** классов.

**Что не умеет:**

- Работать с типами без `virtual`.
- Быть быстрым (проверка в runtime).

**Когда использовать:**

- Наследник имеет **дополнительный** интерфейс.
- Проверка перед специфичной операцией.
- **НЕ для замены виртуальных функций.** Если можно сделать метод
  виртуальным — делайте.

---

## 4. `const_cast`

**Снятие `const`** (или `volatile`). Применяется редко.

```cpp
const int x = 42;
int& y = const_cast<int&>(x);
y = 100;   // UB! x — на самом деле const
```

**Когда нужно:**

- Обход старого C-API, который не принимает `const`.
- Внутренняя изменяемость в `const`-методах (mutable-логика).

**Пример законного применения:**

```cpp
void legacy_function(char* s);   // старый C-API

void wrapper(const char* s) {
    legacy_function(const_cast<char*>(s));   // обещаем, что не меняем
}
```

**Правило:** если объект **изначально** был `const` — менять его через
`const_cast` = UB.

**Современный C++:** для «изменяемости в const-методе» используйте `mutable`:

```cpp
class Cache {
    mutable int cached_value_ = 0;
public:
    int get() const {
        ++cached_value_;   // ок благодаря mutable
        return cached_value_;
    }
};
```

---

## 5. `reinterpret_cast`

**Переинтерпретация битов.** Самый опасный каст.

```cpp
int x = 42;
double* p = reinterpret_cast<double*>(&x);   // ОПАСНО
```

**Где применяется:**

- Приведение указателя к `uintptr_t` (для хешей, отладки).
- Работа с бинарными данными (сериализация).
- Взаимодействие с железом (embedded).

**Когда НЕ применять:**

- Для приведения между классами иерархии — есть `static_cast` / `dynamic_cast`.
- Для числовых преобразований — есть `static_cast`.
- В обычном коде — почти никогда.

**Правило:** если ты пишешь `reinterpret_cast` — остановись и подумай.
Обычно есть более безопасный путь.

---

## 6. C-style cast — НЕ использовать

```cpp
int x = (int)3.14;              // C-style
double* p = (double*)&x;         // опасно
Base* b = (Base*)derived_ptr;    // работает, но непонятно какой каст
```

**Почему плохо:**

- Компилятор сам выбирает между `static_cast`, `const_cast`, `reinterpret_cast`.
- Что именно произошло — **непонятно** из кода.
- Легко случайно снять `const` или переинтерпретировать.

**Правило:** всегда явный каст — `static_cast`, `dynamic_cast` и т.д.

---

## 7. RTTI — `typeid`

**RTTI** — Run-Time Type Information.

```cpp
#include <typeinfo>

Base* p = new Derived;

std::cout << typeid(*p).name() << "\n";      // "Derived"
std::cout << typeid(p).name() << "\n";        // "Base*" (тип указателя)
```

**Что важно:**

- `typeid(*p)` — фактический тип.
- `typeid(p)` — тип указателя.
- Для полиморфных типов — оба разных.

**`typeid` требует:**

- Хотя бы один виртуальный метод (иначе работает без RTTI).
- `#include <typeinfo>`.

**Сравнение:**

```cpp
if (typeid(*p) == typeid(Derived)) {
    // точно Derived (не наследник)
}

if (dynamic_cast<Derived*>(p)) {
    // Derived или его наследник
}
```

**Разница:** `typeid` — **точное** совпадение; `dynamic_cast` — «является ли».

---

## 8. `type_info`

**Что можно:**

```cpp
const std::type_info& info = typeid(*p);

info.name();         // искажённое имя (mangling)
info.hash_code();    // хеш типа
info == typeid(Derived);      // сравнение
info.before(typeid(Base));    // порядок (для сортировки, редко)
```

**Имя искажено:** `Derived` → `7Derived`, `MyClass<int>` → `MyClassIiE`.
Для читаемых имён:

- **Linux:** `abi::__cxa_demangle`.
- **Кроссплатформенно:** `boost::typeindex::type_id<T>().pretty_name()`.

---

## 9. Когда что использовать

| Ситуация | Каст |
|---|---|
| `double` → `int` | `static_cast` |
| `void*` → `T*` (знаешь тип) | `static_cast` |
| Derived → Base (вверх) | `static_cast` (или неявно) |
| Base → Derived (вниз, с проверкой) | `dynamic_cast` |
| Base → Derived (вниз, точно знаешь) | `static_cast` |
| Снять `const` для старого API | `const_cast` |
| Привести `int` к `uintptr_t` | `reinterpret_cast` |
| Привести `float*` к `char*` для чтения байт | `reinterpret_cast` |

**Правило:** **самый узкий каст**. Если подходит `static_cast` — не пиши
`reinterpret_cast`.

---

## 10. Типичные задачи

### Обработчик событий с проверкой типа

```cpp
void process(Event* e) {
    if (auto* click = dynamic_cast<ClickEvent*>(e)) {
        handle_click(*click);
    } else if (auto* key = dynamic_cast<KeyEvent*>(e)) {
        handle_key(*key);
    } else {
        handle_default(*e);
    }
}
```

### Логирование типов

```cpp
void log_type(const Base& b) {
    std::cout << "Тип: " << typeid(b).name() << "\n";
}
```

### Обход старого C-API

```cpp
void old_api(char* buf);   // меняет buf

void wrapper(const std::string& s) {
    std::vector<char> buf(s.begin(), s.end());
    buf.push_back('\0');
    old_api(buf.data());   // не через const_cast — копируем
}
```

**Правило:** `const_cast` — **последний** вариант. Часто лучше скопировать.

---

## 11. Частые ошибки

- **`static_cast` вниз без проверки** — UB при неверном типе.
- **`dynamic_cast` для типа без `virtual`** — ошибка компиляции.
- **`const_cast` объекта, изначально бывшего `const`** — UB.
- **`reinterpret_cast` для иерархии** — UB, используйте `static_cast`/`dynamic_cast`.
- **C-style каст** — непонятно, что произошло.
- **`typeid(*p)` для `p == nullptr`** — исключение `std::bad_typeid`.
- **`typeid` по значению** — срезка; берите `typeid(obj)` у ссылки.
- **Полагаться на имена `typeid().name()`** — они **не переносимы**
  между компиляторами.

---

## Примеры

- [cast_overview.cpp](cast_overview.cpp) — все четыре каста в одном файле
- [dynamic_cast_deep.cpp](dynamic_cast_deep.cpp) — иерархия, поиск типа
- [const_cast_demo.cpp](const_cast_demo.cpp) — `const_cast` и `mutable`
- [reinterpret_cast_demo.cpp](reinterpret_cast_demo.cpp) — переинтерпретация
- [typeid_full.cpp](typeid_full.cpp) — `typeid`, `type_info`, хеш-код
- [rtti_practical.cpp](rtti_practical.cpp) — практическое применение RTTI

## Запуск

**CLion:** выбрать цель → **Shift+F10**.

**Терминал:**

```bash
mkdir build && cd build
cmake ..
cmake --build .
./lesson-27-rtti-casts/cast_overview
```

## Что дальше

Урок 28 — разбор демо экзамена.