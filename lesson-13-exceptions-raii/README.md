# Урок 13. Исключения. RAII. Правило трёх (пяти)

## Цель

Освоить обработку ошибок через исключения, идиому RAII и правило
пяти (включая move-семантику). Познакомиться с `std::expected` из C++23.

## Ключевые понятия

- **Исключение** — объект, описывающий ошибку.
- **`throw` / `try` / `catch`** — выброс и перехват.
- **`std::exception`** — базовый класс для исключений.
- **RAII** — «захват ресурса есть инициализация».
- **Правило трёх / пяти** — что определять в классе, управляющем ресурсами.
- **`std::expected<T, E>`** (C++23) — альтернатива исключениям.

---

## 1. `try` / `catch`

```cpp
try {
    // код, который может бросить исключение
    throw std::runtime_error("что-то пошло не так");
} catch (const std::exception& e) {
    std::cerr << "Ошибка: " << e.what() << "\n";
}
```

- **`throw`** — выброс исключения.
- **`try`** — блок, где ожидаем ошибку.
- **`catch`** — обработчик.
- Поймали — программа продолжает работу.

**Если не поймали** — программа завершается с ошибкой.

---

## 2. Стандартные исключения

Все они — наследники `std::exception`:

| Исключение | Когда |
|---|---|
| `std::runtime_error` | ошибка времени выполнения |
| `std::logic_error` | логическая ошибка |
| `std::invalid_argument` | неверный аргумент |
| `std::out_of_range` | выход за границы |
| `std::length_error` | превышена длина |
| `std::bad_alloc` | не удалось выделить память |

```cpp
#include <stdexcept>

throw std::invalid_argument("x должен быть > 0");
throw std::out_of_range("индекс вне границ");
```

`what()` возвращает текст ошибки.

---

## 3. Несколько `catch`

```cpp
try {
    // ...
} catch (const std::invalid_argument& e) {
    std::cerr << "Неверный аргумент: " << e.what() << "\n";
} catch (const std::out_of_range& e) {
    std::cerr << "Выход за границы: " << e.what() << "\n";
} catch (const std::exception& e) {
    std::cerr << "Другая ошибка: " << e.what() << "\n";
} catch (...) {
    std::cerr << "Неизвестная ошибка\n";
}
```

**Порядок важен:** от **конкретных** к **общим**.
`catch (...)` — последний, ловит всё.

---

## 4. Свои исключения

Наследуемся от `std::exception` или `std::runtime_error`:

```cpp
class BankException : public std::runtime_error {
public:
    explicit BankException(const std::string& msg)
        : std::runtime_error(msg) {}
};

class InsufficientFunds : public BankException {
public:
    explicit InsufficientFunds(const std::string& msg)
        : BankException(msg) {}
};
```

Использование:

```cpp
void withdraw(double amount) {
    if (amount > balance) {
        throw InsufficientFunds("Недостаточно средств");
    }
    balance -= amount;
}
```

**Правило:** свои исключения — от `std::exception` или его наследников.
Тогда `catch (const std::exception&)` поймает их.

---

## 5. RAII — захват ресурса есть инициализация

**Идея:** ресурс захватывается в конструкторе и освобождается
в деструкторе. Даже если брошено исключение — деструктор сработает.

**Без RAII:**

```cpp
void bad() {
    int* p = new int[100];
    // если здесь throw — утечка!
    delete[] p;
}
```

**С RAII:**

```cpp
class Buffer {
private:
    int* data_;
public:
    Buffer(std::size_t n) : data_(new int[n]) {}
    ~Buffer() { delete[] data_; }
};

void good() {
    Buffer b(100);
    // если здесь throw — деструктор освободит память
}
```

**Классические примеры RAII:**

- `std::vector`, `std::string` — память.
- `std::unique_ptr`, `std::shared_ptr` — указатели.
- `std::ifstream`, `std::ofstream` — файлы.
- `std::lock_guard` — мьютексы.

---

## 6. Исключения в конструкторах

Если конструктор бросает — **деструктор не вызывается**
(объект не создан). Но **уже созданные поля** будут уничтожены.

```cpp
class Resource {
private:
    int* a_;
    int* b_;

public:
    Resource() {
        a_ = new int[100];        // может бросить bad_alloc
        try {
            b_ = new int[100];
        } catch (...) {
            delete[] a_;           // освобождаем вручную
            throw;
        }
    }
};
```

**Проще — через RAII-поля:**

```cpp
class Resource {
private:
    std::vector<int> a_;
    std::vector<int> b_;
public:
    Resource() : a_(100), b_(100) {}
    // vector сам разберётся
};
```

---

## 7. Правило трёх / пяти

**Правило трёх:** если класс определяет **хотя бы одно**:

1. деструктор,
2. копирующий конструктор,
3. копирующее присваивание,

— то нужно определить **все три**.

**Правило пяти (C++11):** плюс ещё:

4. move-конструктор,
5. move-присваивание.

### Пример: класс с ресурсом

```cpp
class Buffer {
private:
    int* data_;
    std::size_t size_;

public:
    // Конструктор
    Buffer(std::size_t n) : data_(new int[n]), size_(n) {}

    // 1. Деструктор
    ~Buffer() { delete[] data_; }

    // 2. Копирование
    Buffer(const Buffer& o) : data_(new int[o.size_]), size_(o.size_) {
        std::copy(o.data_, o.data_ + size_, data_);
    }

    // 3. Присваивание
    Buffer& operator=(const Buffer& o) {
        if (this != &o) {
            delete[] data_;
            size_ = o.size_;
            data_ = new int[size_];
            std::copy(o.data_, o.data_ + size_, data_);
        }
        return *this;
    }

    // 4. Move-конструктор (C++11)
    Buffer(Buffer&& o) noexcept
        : data_(o.data_), size_(o.size_) {
        o.data_ = nullptr;
        o.size_ = 0;
    }

    // 5. Move-присваивание (C++11)
    Buffer& operator=(Buffer&& o) noexcept {
        if (this != &o) {
            delete[] data_;
            data_ = o.data_;
            size_ = o.size_;
            o.data_ = nullptr;
            o.size_ = 0;
        }
        return *this;
    }
};
```

**Move-семантика — подробно в уроке 15.**

---

## 8. Правило нуля (C++11)

**Если класс не управляет ресурсами напрямую — ничего не определяйте.**
Компилятор сгенерирует правильно.

```cpp
class Point {
private:
    int x_, y_;
public:
    Point(int x, int y) : x_(x), y_(y) {}
    // Никаких деструкторов, копирований, перемещений — всё работает
};
```

**Правило нуля — предпочтительнее.** Используйте `std::vector`, `std::string`,
`std::unique_ptr` — и не пишите свою ручную память.

---

## 9. `noexcept`

**`noexcept`** — обещание, что функция **не бросает** исключения.

```cpp
int safe_divide(int a, int b) noexcept {
    if (b == 0) return 0;   // не throw
    return a / b;
}
```

**Зачем:**

- Компилятор оптимизирует.
- `std::vector` использует **move**, если move-конструктор `noexcept`.
- Если функция с `noexcept` бросит — `std::terminate`.

**Правило:** помечайте `noexcept` функции, которые точно не бросают.
Особенно — **move-конструкторы** и **деструкторы**.

---

## 10. `std::expected<T, E>` (C++23)

**Альтернатива исключениям** для ожидаемых ошибок.

```cpp
#include <expected>

std::expected<int, std::string> parse_int(const std::string& s) {
    try {
        return std::stoi(s);
    } catch (...) {
        return std::unexpected("не число");
    }
}

int main() {
    auto result = parse_int("123");
    if (result) {
        std::cout << "OK: " << *result << "\n";
    }

    auto bad = parse_int("abc");
    if (!bad) {
        std::cout << "Ошибка: " << bad.error() << "\n";
    }
}
```

**Когда использовать:**

- Ошибка — **ожидаемая** часть работы (парсинг, поиск).
- Не хотим использовать исключения (производительность, стиль).

**Когда исключения лучше:**

- Ошибка **исключительная** (нет памяти, повреждён файл).
- Нельзя обработать локально.

---

## 11. Типичные задачи

### Безопасное деление

```cpp
int safe_div(int a, int b) {
    if (b == 0) {
        throw std::invalid_argument("деление на ноль");
    }
    return a / b;
}
```

### Банк: снятие средств

```cpp
void withdraw(double amount) {
    if (amount <= 0)
        throw std::invalid_argument("сумма должна быть > 0");
    if (amount > balance_)
        throw InsufficientFunds("недостаточно средств");
    balance_ -= amount;
}
```

### RAII для файла

```cpp
{
    std::ofstream fout("file.txt");
    fout << "data\n";
    // даже при исключении файл закроется
}
```

### RAII для мьютекса

```cpp
#include <mutex>

std::mutex m;

void safe_increment() {
    std::lock_guard<std::mutex> lock(m);
    ++shared_counter;
    // мьютекс освободится автоматически
}
```

---

## 12. Частые ошибки

- **Ловить по значению** вместо `const&` — копирование, срезка.
  Правильно: `catch (const std::exception& e)`.
- **Порядок `catch`** от общего к частному — частные не сработают.
  Правильно: от **частных** к **общим**.
- **Исключение в деструкторе** — UB. Деструкторы — `noexcept`.
- **Утечка при исключении в конструкторе** — используйте RAII.
- **`throw;` без аргумента** вне `catch` — `std::terminate`.
- **Забыли `noexcept` на move-конструкторе** — `vector` будет копировать.
- **Ловить `...` без обработки** — «молчаливое проглатывание».

---

## Примеры

- [try_catch.cpp](try_catch.cpp) — базовый `try` / `catch`
- [multiple_catch.cpp](multiple_catch.cpp) — несколько `catch`, порядок
- [custom_exception.cpp](custom_exception.cpp) — свои исключения
- [raii_demo.cpp](raii_demo.cpp) — RAII: деструктор при исключении
- [rule_of_five.cpp](rule_of_five.cpp) — полный класс с пятью операциями
- [expected_demo.cpp](expected_demo.cpp) — `std::expected` (C++23)

## Запуск

**CLion:** выбрать цель → **Shift+F10**.

**Терминал:**

```bash
mkdir build && cd build
cmake ..
cmake --build .
./lesson-13-exceptions-raii/try_catch
```

## Что дальше

Урок 14 — умные указатели: `unique_ptr`, `shared_ptr`, `weak_ptr`.