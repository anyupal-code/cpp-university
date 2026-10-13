# Урок 7. Массивы. Статические и динамические. Связь с указателями

## Цель

Освоить хранение наборов однотипных данных: статические массивы,
`std::array`, `std::vector`, устаревшие динамические массивы через `new[]`.

## Ключевые понятия

- **Массив** — набор элементов одного типа, доступ по индексу.
- **Статический массив** — на стеке, размер известен при компиляции.
- **`std::array`** — обёртка над статическим массивом с методами.
- **`std::vector`** — динамический массив из STL.
- **`new[]` / `delete[]`** — ручное выделение динамического массива.
- **Итерация** — обход элементов.

---

## 1. Статический массив

```cpp
int arr[5];                    // 5 int, не инициализированы
int a[5] = {10, 20, 30, 40, 50};
int b[] = {1, 2, 3};           // размер выведен автоматически = 3
int c[5] = {1, 2};             // {1, 2, 0, 0, 0} — остальные нули
int d[5] = {};                 // {0, 0, 0, 0, 0}
```

**Индексация — с 0:**

```cpp
int arr[3] = {10, 20, 30};
std::cout << arr[0] << "\n";   // 10
std::cout << arr[2] << "\n";   // 30
// arr[3] — выход за границы, UB
```

**Размер:**

```cpp
int arr[5];
std::size_t n = sizeof(arr) / sizeof(arr[0]);   // 5
```

- `sizeof(arr)` — размер всего массива в байтах (20).
- `sizeof(arr[0])` — размер элемента (4).
- Частное — количество элементов.

**В C++17** появился `std::size(arr)` из `<iterator>`:

```cpp
#include <iterator>
std::size_t n = std::size(arr);
```

**Важно:** имя массива — **не указатель**, но **преобразуется** в указатель
на первый элемент при передаче в функцию.

---

## 2. Обход массива

**Индексный цикл:**

```cpp
for (int i = 0; i < 5; ++i) {
    std::cout << arr[i] << " ";
}
```

**Range-based `for` (C++11):**

```cpp
for (int x : arr) {
    std::cout << x << " ";
}

for (int& x : arr) {   // по ссылке — для изменения
    x *= 2;
}
```

**Через указатель** (см. урок 5):

```cpp
for (int* p = arr; p < arr + 5; ++p) {
    std::cout << *p << " ";
}
```

---

## 3. Типичные алгоритмы

### Сумма и среднее

```cpp
int sum = 0;
for (int x : arr) sum += x;
double avg = static_cast<double>(sum) / n;
```

### Минимум и максимум

```cpp
int mn = arr[0], mx = arr[0];
for (int i = 1; i < n; ++i) {
    if (arr[i] < mn) mn = arr[i];
    if (arr[i] > mx) mx = arr[i];
}
```

**В C++20+** — через ranges:

```cpp
#include <algorithm>
auto [mn, mx] = std::ranges::minmax(arr);
```

### Поиск

```cpp
int target = 30;
bool found = false;
for (int i = 0; i < n; ++i) {
    if (arr[i] == target) {
        found = true;
        break;
    }
}
```

**В STL:** `std::find(arr, arr + n, target)`.

### Реверс

```cpp
for (int i = 0; i < n / 2; ++i) {
    std::swap(arr[i], arr[n - 1 - i]);
}
```

**В STL:** `std::reverse(arr, arr + n)`.

---

## 4. `std::array<T, N>` (C++11)

Обёртка над статическим массивом с методами. Размер — **часть типа**.

```cpp
#include <array>

std::array<int, 5> arr = {10, 20, 30, 40, 50};

std::cout << arr.size() << "\n";       // 5
std::cout << arr[0] << "\n";           // 10
std::cout << arr.at(2) << "\n";        // 30, с проверкой границ

for (int x : arr) std::cout << x << " ";
```

**Преимущества:**

- `.size()`, `.at()`, `.front()`, `.back()`, итераторы.
- Копируется целиком (в отличие от C-массива).
- Не теряет размер при передаче в функцию.

**Когда использовать:** когда размер известен на этапе компиляции
и хочется удобство STL.

---

## 5. `std::vector<T>` — динамический массив

**Основной инструмент** для работы с массивами в современном C++.

```cpp
#include <vector>

std::vector<int> v;                    // пустой
std::vector<int> v2 = {1, 2, 3, 4, 5}; // с инициализацией
std::vector<int> v3(10);               // 10 нулей
std::vector<int> v4(10, 42);           // 10 элементов, все 42
```

### Основные методы

| Метод | Что делает |
|---|---|
| `push_back(x)` | добавить в конец |
| `pop_back()` | удалить последний |
| `size()` | количество элементов |
| `empty()` | пуст ли |
| `clear()` | удалить все |
| `resize(n)` | изменить размер |
| `v[i]` | доступ без проверки |
| `v.at(i)` | доступ с проверкой границ |
| `front()` / `back()` | первый / последний |
| `insert(pos, x)` | вставить |
| `erase(pos)` | удалить |

### Пример

```cpp
std::vector<int> v;

v.push_back(10);
v.push_back(20);
v.push_back(30);

std::cout << v.size() << "\n";      // 3
std::cout << v[0] << "\n";          // 10
std::cout << v.at(2) << "\n";       // 30

for (int x : v) std::cout << x << " ";
```

### `vector` растёт автоматически

```cpp
for (int i = 0; i < 100; ++i) {
    v.push_back(i);    // размер растёт по мере надобности
}
```

- Внутри `vector` — динамический массив.
- При нехватке места — перевыделение (ёмкость удваивается).
- **`capacity()`** — текущая ёмкость.

### `vector` и память

**Освобождается автоматически** — не нужен `delete`. RAII.

---

## 6. `vector` с алгоритмами

```cpp
#include <vector>
#include <algorithm>
#include <numeric>

std::vector<int> v = {5, 2, 8, 1, 9, 3};

// Сумма
int sum = std::accumulate(v.begin(), v.end(), 0);

// Минимум / максимум
auto mn = *std::min_element(v.begin(), v.end());
auto mx = *std::max_element(v.begin(), v.end());

// Сортировка
std::sort(v.begin(), v.end());

// Поиск
auto it = std::find(v.begin(), v.end(), 8);
if (it != v.end()) {
    std::cout << "Найдено на позиции " << (it - v.begin()) << "\n";
}

// Реверс
std::reverse(v.begin(), v.end());

// Range-based for
for (int x : v) std::cout << x << " ";
```

**Подробно про алгоритмы STL — в уроке 19.**

---

## 7. Динамические массивы через `new[]` (устаревший способ)

До STL так делали все. Сейчас — **не рекомендуется**.

```cpp
int n;
std::cin >> n;

int* arr = new int[n];    // выделили
for (int i = 0; i < n; ++i) {
    arr[i] = i * 10;
}

// ... используем ...

delete[] arr;             // освободили
arr = nullptr;
```

**Проблемы:**

- Забыл `delete[]` — **утечка**.
- Двойный `delete[]` — **UB**.
- Размер нужно **хранить отдельно** (`n`).
- Нет `.size()`, `.push_back`, итераторов.

**Замена:** `std::vector<int>` — делает всё то же, но безопаснее.

---

## 8. Что использовать

| Ситуация | Инструмент |
|---|---|
| Размер известен, не меняется | `std::array<T, N>` |
| Размер известен, но хочется C-стиль | `T arr[N]` |
| Размер меняется | `std::vector<T>` |
| Динамический массив без STL | `new[]` (не рекомендуется) |

**Правило для современного C++:**

- **`std::vector`** — по умолчанию.
- **`std::array`** — если размер известен и фиксирован.
- **C-массив** — только для взаимодействия с C-API.
- **`new[]`** — забудь.

---

## 9. Типичные задачи

### Сумма, среднее, мин, макс

```cpp
int sum = 0;
for (int x : v) sum += x;
double avg = static_cast<double>(sum) / v.size();

auto [mn, mx] = std::ranges::minmax(v);   // C++20
```

### Поиск

```cpp
auto it = std::find(v.begin(), v.end(), target);
bool found = (it != v.end());
```

### Удалить все чётные

```cpp
std::erase_if(v, [](int x) { return x % 2 == 0; });   // C++20
```

До C++20:

```cpp
v.erase(std::remove_if(v.begin(), v.end(),
                       [](int x) { return x % 2 == 0; }),
        v.end());
```

### Реверс

```cpp
std::reverse(v.begin(), v.end());
```

### Сортировка

```cpp
std::sort(v.begin(), v.end());                    // по возрастанию
std::sort(v.begin(), v.end(), std::greater<>{});  // по убыванию
```

### Свой компаратор

```cpp
std::sort(v.begin(), v.end(),
          [](int a, int b) { return a > b; });
```

---

## 10. Частые ошибки

- **Выход за границы** — `arr[n]` вместо `arr[n-1]`. UB.
- **`sizeof(arr) / sizeof(arr[0])`** не работает для указателя:
  ```cpp
  void f(int arr[]) {
      // sizeof(arr) — размер указателя, не массива!
  }
  ```
- **Забыли `delete[]`** для `new[]` — утечка.
- **`delete` вместо `delete[]`** — UB.
- **Использование `vector::operator[]` без проверки** — UB,
  если индекс вне границ. Для проверки — `.at(i)`.
- **Изменение `vector` внутри range-based `for`** — UB
  (итераторы могут «поехать»).
- **Сравнение `size()` с `int`** — `size()` возвращает `size_t`
  (беззнаковый), знаковое превращается в беззнаковое.

---

## Примеры

- [static_array.cpp](static_array.cpp) — статические массивы
- [array_algorithms.cpp](array_algorithms.cpp) — сумма, мин/макс, поиск, реверс
- [std_array.cpp](std_array.cpp) — `std::array`
- [vector_basic.cpp](vector_basic.cpp) — `std::vector`, `push_back`, обход
- [vector_algorithms.cpp](vector_algorithms.cpp) — сортировка, поиск, удаление
- [dynamic_array.cpp](dynamic_array.cpp) — `new[]` / `delete[]`

## Запуск

**CLion:** выбрать цель → **Shift+F10**.

**Терминал:**

```bash
mkdir build && cd build
cmake ..
cmake --build .
./lesson-07-arrays/static_array
```

## Что дальше

Урок 8 — двумерные массивы, строки, файлы.