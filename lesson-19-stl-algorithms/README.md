# Урок 19. Алгоритмы STL: `sort`, `find`, ranges, лямбды

## Цель

Освоить стандартные алгоритмы STL: сортировку, поиск, преобразование
и агрегацию. Познакомиться с лямбдами и ranges из C++20.

## Ключевые понятия

- **Алгоритм STL** — готовая функция для работы с диапазоном.
- **Диапазон** — пара итераторов `[begin, end)`.
- **Лямбда** — анонимная функция на месте.
- **Предикат** — функция, возвращающая `bool`.
- **Ranges (C++20)** — новый способ работы с последовательностями.
- **Проекция** — как преобразовать элемент перед сравнением.

---

## 1. Заголовок `<algorithm>`

Все алгоритмы — в `<algorithm>`, кроме числовых — в `<numeric>`.

```cpp
#include <algorithm>
#include <numeric>
```

**Идея:** алгоритм принимает **диапазон** `[first, last)` и **не знает**,
что за контейнер. Работает с `vector`, `list`, `deque`, массивом.

---

## 2. Поиск

### `std::find` — найти значение

```cpp
std::vector<int> v = {5, 2, 8, 1, 9};

auto it = std::find(v.begin(), v.end(), 8);
if (it != v.end()) {
    std::cout << "Найдено на позиции " << (it - v.begin()) << "\n";
}
```

### `std::find_if` — найти по условию

```cpp
auto it = std::find_if(v.begin(), v.end(),
                       [](int x) { return x > 5; });
```

### `std::count` / `std::count_if`

```cpp
int n1 = std::count(v.begin(), v.end(), 5);
int n2 = std::count_if(v.begin(), v.end(),
                       [](int x) { return x % 2 == 0; });
```

### `std::all_of`, `std::any_of`, `std::none_of`

```cpp
bool all_positive = std::all_of(v.begin(), v.end(),
                                [](int x) { return x > 0; });
bool any_even = std::any_of(v.begin(), v.end(),
                            [](int x) { return x % 2 == 0; });
bool none_negative = std::none_of(v.begin(), v.end(),
                                  [](int x) { return x < 0; });
```

### `std::min_element` / `std::max_element`

```cpp
auto mn = std::min_element(v.begin(), v.end());
auto mx = std::max_element(v.begin(), v.end());
std::cout << *mn << " " << *mx << "\n";
```

---

## 3. Сортировка

### `std::sort`

```cpp
std::sort(v.begin(), v.end());                    // возрастание
std::sort(v.begin(), v.end(), std::greater<>{});  // убывание
```

**Сложность:** O(n log n). **Не устойчивая.**

### Свой компаратор

```cpp
std::sort(v.begin(), v.end(),
          [](int a, int b) { return a > b; });
```

### `std::stable_sort`

Сохраняет порядок **равных** элементов:

```cpp
std::stable_sort(v.begin(), v.end(), cmp);
```

### `std::partial_sort`

Сортирует только первые K:

```cpp
std::partial_sort(v.begin(), v.begin() + 3, v.end());
// первые 3 — минимальные, отсортированы
```

### `std::nth_element`

Ставит на место `n` «правильный» элемент, слева — меньше, справа — больше:

```cpp
std::nth_element(v.begin(), v.begin() + v.size() / 2, v.end());
// v[n/2] — медиана
```

**O(n) в среднем.**

### `std::is_sorted`

```cpp
if (std::is_sorted(v.begin(), v.end())) {
    std::cout << "отсортирован\n";
}
```

---

## 4. Преобразование

### `std::transform` — применить функцию

```cpp
std::vector<int> src = {1, 2, 3, 4, 5};
std::vector<int> dst(src.size());

std::transform(src.begin(), src.end(), dst.begin(),
               [](int x) { return x * x; });
// dst = {1, 4, 9, 16, 25}
```

### `std::transform` с двумя диапазонами

```cpp
std::vector<int> a = {1, 2, 3};
std::vector<int> b = {10, 20, 30};
std::vector<int> c(3);

std::transform(a.begin(), a.end(), b.begin(), c.begin(),
               [](int x, int y) { return x + y; });
// c = {11, 22, 33}
```

### `std::for_each` — выполнить действие

```cpp
std::for_each(v.begin(), v.end(),
              [](int x) { std::cout << x << " "; });
```

### `std::copy`, `std::copy_if`

```cpp
std::vector<int> dst(v.size());
std::copy(v.begin(), v.end(), dst.begin());

std::vector<int> evens;
std::copy_if(v.begin(), v.end(), std::back_inserter(evens),
             [](int x) { return x % 2 == 0; });
```

### `std::fill`, `std::iota`

```cpp
std::fill(v.begin(), v.end(), 0);      // все 0

std::vector<int> seq(10);
std::iota(seq.begin(), seq.end(), 1);  // 1, 2, 3, ..., 10
```

### `std::remove_if` + `erase` — удаление

```cpp
v.erase(std::remove_if(v.begin(), v.end(),
                       [](int x) { return x % 2 == 0; }),
        v.end());
```

**C++20:** короче —

```cpp
std::erase_if(v, [](int x) { return x % 2 == 0; });
```

---

## 5. Числовые алгоритмы (`<numeric>`)

### `std::accumulate` — сумма / свёртка

```cpp
int sum = std::accumulate(v.begin(), v.end(), 0);
int prod = std::accumulate(v.begin(), v.end(), 1,
                           std::multiplies<>());
```

### `std::inner_product` — скалярное произведение

```cpp
int dot = std::inner_product(a.begin(), a.end(),
                             b.begin(), 0);
```

### `std::partial_sum` — префиксные суммы

```cpp
std::vector<int> prefix(v.size());
std::partial_sum(v.begin(), v.end(), prefix.begin());
// {1, 2, 3, 4} -> {1, 3, 6, 10}
```

### `std::iota` — заполнить последовательностью

```cpp
std::iota(v.begin(), v.end(), 1);
```

### `std::gcd`, `std::lcm` (C++17)

```cpp
int g = std::gcd(12, 18);    // 6
int l = std::lcm(4, 6);       // 12
```

---

## 6. Лямбды

**Лямбда** — анонимная функция. Пишется прямо в месте использования.

```cpp
auto f = [](int x) { return x * x; };
std::cout << f(5) << "\n";    // 25
```

### Синтаксис

```cpp
[capture](parameters) -> return_type { body }
```

### Захват переменных

```cpp
int base = 10;

// [base] — захватить по значению
auto add = [base](int x) { return x + base; };

// [&base] — по ссылке
auto inc = [&base](int x) { base += x; };

// [=] — все по значению
// [&] — все по ссылке
// [=, &base] — все по значению, base по ссылке
// [x = 5] — инициализация (C++14)
```

### `mutable`

По умолчанию захваченные по значению — `const`. `mutable` разрешает менять:

```cpp
int counter = 0;
auto f = [counter]() mutable { return ++counter; };
f(); f(); f();
std::cout << counter << "\n";    // 0 — снаружи не изменилось
```

### Generic-лямбды (C++14)

```cpp
auto print = [](const auto& x) { std::cout << x << "\n"; };
print(42);
print("hello");
print(3.14);
```

---

## 7. Ranges (C++20)

**Ranges** — новый способ писать алгоритмы. Короче и читаемее.

### Прямо на контейнере

```cpp
#include <ranges>

std::vector<int> v = {5, 2, 8, 1, 9};

std::ranges::sort(v);              // без begin/end
auto it = std::ranges::find(v, 8);
```

### Views — ленивые преобразования

```cpp
using namespace std::views;

std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

// Чётные, умноженные на 2, первые 3
auto result = v
    | std::views::filter([](int x) { return x % 2 == 0; })
    | std::views::transform([](int x) { return x * 2; })
    | std::views::take(3);

for (int x : result) {
    std::cout << x << " ";    // 4 8 12
}
```

**Что произошло:**

- `filter` — оставили чётные.
- `transform` — умножили на 2.
- `take(3)` — первые 3.
- **Ничего не скопировано** — вычисляется лениво.

### Полезные views

| View | Что делает |
|---|---|
| `filter` | оставить подходящие |
| `transform` | преобразовать |
| `take(n)` | первые n |
| `drop(n)` | пропустить первые n |
| `reverse` | обратный порядок |
| `iota` | последовательность |

### `ranges` + алгоритмы

```cpp
std::ranges::sort(v);
std::ranges::reverse(v);
std::ranges::find(v, 8);
std::ranges::count_if(v, [](int x) { return x > 5; });
```

**Проекция** — можно указать, по какому полю сравнивать:

```cpp
struct Student {
    std::string name;
    double average;
};

std::vector<Student> students = {...};

// Сортировка по average
std::ranges::sort(students, {}, &Student::average);
```

**Очень удобно** — без лямбды-компаратора.

---

## 8. Типичные задачи

### Удалить все чётные

```cpp
std::erase_if(v, [](int x) { return x % 2 == 0; });   // C++20
```

### Найти второй по величине

```cpp
std::nth_element(v.begin(), v.begin() + 1, v.end(), std::greater<>());
std::cout << v[1] << "\n";
```

### Все положительные?

```cpp
bool ok = std::ranges::all_of(v, [](int x) { return x > 0; });
```

### Сумма квадратов чётных

```cpp
int sum = 0;
for (int x : v | std::views::filter([](int x) { return x % 2 == 0; })
               | std::views::transform([](int x) { return x * x; })) {
    sum += x;
}
```

### Сортировка по убыванию длины строк

```cpp
std::sort(words.begin(), words.end(),
          [](const std::string& a, const std::string& b) {
              return a.size() > b.size();
          });
```

### Уникальные значения

```cpp
std::sort(v.begin(), v.end());
v.erase(std::unique(v.begin(), v.end()), v.end());
```

---

## 9. Компараторы: правила

**Компаратор `cmp(a, b)`** должен быть **строгим слабым порядком**:

- `cmp(a, a) == false` — ничто не меньше себя.
- Если `cmp(a, b)` и `cmp(b, c)` — то `cmp(a, c)`.
- Если `!cmp(a, b)` и `!cmp(b, a)` — `a` и `b` эквивалентны.

**Ошибка:** `<=` вместо `<`. Приводит к UB.

```cpp
// Плохо:
[](int a, int b) { return a <= b; }

// Хорошо:
[](int a, int b) { return a < b; }
```

---

## 10. Частые ошибки

- **`sort` на `list`** — не работает. У `list` свой `.sort()`.
- **Компаратор с `<=`** — UB.
- **`remove_if` без `erase`** — элементы не удаляются, а «сдвигаются».
  Нужен `erase-remove idiom` или `std::erase_if`.
- **Итераторы после изменения контейнера** — могут «поехать».
- **Забыли `#include <algorithm>`** или `<numeric>`.
- **`std::accumulate` с `int` для `double`** — потеря точности.
  Начинайте с `0.0`.
- **Лямбда захватывает по ссылке локальную переменную**, которая умрёт.

---

## Примеры

- [algo_basic.cpp](algo_basic.cpp) — `find`, `count`, `all_of`, `min/max`
- [algo_transform.cpp](algo_transform.cpp) — `transform`, `copy_if`, `fill`, `iota`
- [algo_predicates.cpp](algo_predicates.cpp) — предикаты, `find_if`, `count_if`, `remove_if`
- [algo_numeric.cpp](algo_numeric.cpp) — `accumulate`, `partial_sum`, `inner_product`
- [ranges_demo.cpp](ranges_demo.cpp) — ranges, views, pipe
- [lambdas_demo.cpp](lambdas_demo.cpp) — лямбды, захваты, `mutable`, generic

## Запуск

**CLion:** выбрать цель → **Shift+F10**.

**Терминал:**

```bash
mkdir build && cd build
cmake ..
cmake --build .
./lesson-19-stl-algorithms/algo_basic
```

## Что дальше

Урок 20 — разбор демо контрольной работы (модуль 2).