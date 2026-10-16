# Урок 18. Ассоциативные контейнеры: `map`, `set`, `unordered_map`

## Цель

Освоить ассоциативные контейнеры — словари и множества. Понять разницу
между упорядоченными (`map`, `set`) и хеш-таблицами
(`unordered_map`, `unordered_set`).

## Ключевые понятия

- **`std::map<K, V>`** — упорядоченный словарь «ключ → значение».
- **`std::set<T>`** — упорядоченное множество уникальных элементов.
- **`std::unordered_map`** — хеш-таблица «ключ → значение».
- **`std::unordered_set`** — хеш-множество.
- **Красно-чёрное дерево** — основа `map` / `set`, O(log n).
- **Хеш-таблица** — основа `unordered_*`, O(1) в среднем.
- **Хеш-функция** — превращает ключ в число для быстрого поиска.

---

## 1. `std::map` — упорядоченный словарь

**Что это:** красно-чёрное дерево. Ключи **отсортированы** по `<`.

### Создание и вставка

```cpp
#include <map>

std::map<std::string, int> ages;

ages["Иван"] = 25;                 // вставка или обновление
ages["Мария"] = 30;
ages.insert({"Пётр", 28});         // через insert
ages.emplace("Олег", 22);          // через emplace
```

### Доступ

```cpp
std::cout << ages["Иван"] << "\n";      // 25

// ОСТОРОЖНО: [] СОЗДАЁТ элемент, если его нет!
std::cout << ages["Неизвестный"] << "\n";  // 0, но элемент создан
```

**Правило:** для чтения используйте `find` или `at`, а не `[]`.

```cpp
// Безопасно
auto it = ages.find("Иван");
if (it != ages.end()) {
    std::cout << it->second << "\n";
}

// at() — с исключением
try {
    std::cout << ages.at("Иван") << "\n";
} catch (const std::out_of_range&) {
    std::cout << "нет ключа\n";
}
```

### C++20: `contains`

```cpp
if (ages.contains("Иван")) {
    std::cout << "есть\n";
}
```

### Обход

```cpp
for (const auto& [name, age] : ages) {      // структурированные привязки
    std::cout << name << ": " << age << "\n";
}
```

**Порядок обхода — по возрастанию ключей** (отсортирован).

### Удаление

```cpp
ages.erase("Пётр");           // по ключу
ages.erase(it);                // по итератору
```

### Основные операции

| Операция | Метод |
|---|---|
| Вставка/обновление | `m[key] = value` |
| Вставка | `m.insert({k, v})`, `m.emplace(k, v)` |
| Поиск | `m.find(k)`, `m.contains(k)`, `m.count(k)` |
| Доступ | `m[k]` (создаёт), `m.at(k)` (исключение) |
| Удаление | `m.erase(k)` |
| Размер | `m.size()` |
| Обход | `for (const auto& [k, v] : m)` |

---

## 2. `std::set` — упорядоченное множество

**Что это:** красно-чёрное дерево **уникальных** элементов.

### Создание

```cpp
#include <set>

std::set<int> s = {5, 2, 8, 1, 9};
// внутри: {1, 2, 5, 8, 9} — отсортировано автоматически
```

### Вставка

```cpp
s.insert(3);
s.insert(3);      // не добавит — дубликат
std::cout << s.size() << "\n";
```

### Поиск

```cpp
if (s.contains(5)) {        // C++20
    std::cout << "есть 5\n";
}

auto it = s.find(8);
if (it != s.end()) std::cout << *it << "\n";
```

### Обход

```cpp
for (int x : s) std::cout << x << " ";
// 1 2 3 5 8 9
```

### Удаление

```cpp
s.erase(3);
```

**Когда использовать:**

- Уникальные элементы.
- Проверка «есть / нет».
- Отсортированный обход.
- Удаление дубликатов.

---

## 3. `std::unordered_map` — хеш-таблица

**Что это:** хеш-таблица. **O(1)** в среднем на операции.
Порядок элементов **не определён**.

```cpp
#include <unordered_map>

std::unordered_map<std::string, int> freq;

freq["apple"] = 3;
freq["banana"] = 5;
freq["cherry"] = 2;

for (const auto& [word, count] : freq) {
    std::cout << word << ": " << count << "\n";
}
// порядок ПРОИЗВОЛЬНЫЙ
```

### Что общего с `map`

- Тот же интерфейс: `[]`, `insert`, `find`, `erase`, `contains`.
- Те же структурированные привязки.

### Отличия

| Свойство | `map` | `unordered_map` |
|---|---|---|
| Внутри | дерево | хеш-таблица |
| Сложность | O(log n) | O(1) в среднем |
| Порядок | отсортирован | не определён |
| Требования к ключу | `operator<` | `std::hash` и `operator==` |
| Память | компактнее | больше (хеш-таблица) |

### `std::unordered_set`

То же — для множеств:

```cpp
#include <unordered_set>

std::unordered_set<int> s = {1, 2, 3};
s.insert(4);
if (s.contains(2)) std::cout << "есть\n";
```

---

## 4. Что выбрать

| Задача | Контейнер |
|---|---|
| Словарь, порядок важен | `map` |
| Словарь, скорость важнее | `unordered_map` |
| Множество, порядок важен | `set` |
| Множество, скорость важнее | `unordered_set` |
| Дубликаты допустимы | `multimap`, `multiset` |

**Правило:** если порядок **не важен** — берите `unordered_*`.
Если нужен **отсортированный обход** — `map` / `set`.

**На практике:** `unordered_map` обычно быстрее в 2–5 раз,
но разница заметна только на больших данных (>10 000 элементов).

---

## 5. Операции над множествами

```cpp
std::set<int> a = {1, 2, 3, 4, 5};
std::set<int> b = {4, 5, 6, 7};

std::set<int> result;

// Объединение
std::set_union(a.begin(), a.end(),
               b.begin(), b.end(),
               std::inserter(result, result.begin()));

// Пересечение
std::set_intersection(a.begin(), a.end(),
                      b.begin(), b.end(),
                      std::inserter(result, result.begin()));

// Разность
std::set_difference(a.begin(), a.end(),
                    b.begin(), b.end(),
                    std::inserter(result, result.begin()));
```

**C++20** добавил `std::set_union` и другие в ranges-версии.

**Важно:** множества должны быть **отсортированы**
(для `unordered_set` это **не сработает**).

---

## 6. Свой хеш и `operator==`

Для `unordered_map` / `unordered_set` с **пользовательским типом** —
нужны `std::hash` и `operator==`.

**Пример: точка на плоскости**

```cpp
struct Point {
    int x, y;
    bool operator==(const Point& o) const {
        return x == o.x && y == o.y;
    }
};

struct PointHash {
    std::size_t operator()(const Point& p) const noexcept {
        std::size_t h1 = std::hash<int>{}(p.x);
        std::size_t h2 = std::hash<int>{}(p.y);
        return h1 ^ (h2 << 1);   // простая комбинация
    }
};

std::unordered_set<Point, PointHash> points;
points.insert({1, 2});
points.insert({1, 2});   // не добавится

// Или в unordered_map:
std::unordered_map<Point, int, PointHash> dist;
```

**Что важно:**

- Хеш должен быть **стабильным** — одинаковый для одинаковых объектов.
- Для хорошей производительности — **равномерно распределённым**.
- `operator==` — согласован с хешем: если `a == b`, то `hash(a) == hash(b)`.

---

## 7. `multimap` и `multiset`

Допускают **дубликаты ключей**.

```cpp
std::multimap<std::string, int> scores;
scores.insert({"Иван", 5});
scores.insert({"Иван", 4});     // второй раз — можно
scores.insert({"Иван", 3});

auto range = scores.equal_range("Иван");
for (auto it = range.first; it != range.second; ++it) {
    std::cout << it->second << "\n";    // 3, 4, 5 (отсортированы)
}
```

`std::multiset` — то же для множеств.

**Применение:** «список» значений по одному ключу.

---

## 8. Производительность

- **`map` / `set`:** O(log n). Стабильно.
- **`unordered_map` / `unordered_set`:** O(1) в среднем,
  но **O(n) в худшем** (если все ключи в одну «корзину»).
- **Память:** `unordered_*` едят больше (нужны корзины).
- **Обход:** `map` быстрее (кэш-локальность узлов ниже, но обход
  последовательный; `unordered_map` — разбросанные корзины).

**Правило:** если элементов **> 1000** и порядок не важен — `unordered_*`.
Иначе — `map` / `set`.

---

## 9. Типичные задачи

### Подсчёт частот слов

```cpp
std::map<std::string, int> freq;
std::istringstream iss(text);
std::string w;
while (iss >> w) ++freq[w];

for (const auto& [word, count] : freq) {
    std::cout << word << ": " << count << "\n";
}
```

### Группировка по ключу

```cpp
std::map<std::string, std::vector<int>> groups;
groups["чётные"].push_back(2);
groups["чётные"].push_back(4);
groups["нечётные"].push_back(3);
```

### Проверка уникальности

```cpp
std::unordered_set<int> seen;
for (int x : data) {
    if (seen.contains(x)) return false;
    seen.insert(x);
}
return true;
```

### Кэш

```cpp
std::unordered_map<std::string, std::string> cache;

std::string get(const std::string& key) {
    auto it = cache.find(key);
    if (it != cache.end()) return it->second;

    std::string value = compute(key);
    cache[key] = value;
    return value;
}
```

### Обратный индекс

```cpp
std::map<std::string, std::set<int>> index;   // слово → номера строк
index["hello"].insert(1);
index["hello"].insert(5);
index["world"].insert(2);
```

---

## 10. Частые ошибки

- **`m[key]` создаёт элемент**, если его нет. Для чтения — `find` или `at`.
- **Ключ в `map` должен быть сравним** через `<`. Иначе — ошибка.
- **`unordered_map` не сохраняет порядок** — не полагайтесь на него.
- **Свой тип в `unordered_map`** — нужны `std::hash` и `operator==`.
- **Итератор после `insert` / `erase`** может стать недействительным.
  В `map`/`set` итераторы **стабильны** — кроме удалённого.
- **Изменение ключа через итератор** — нельзя. `map` хранит `pair<const K, V>`.
- **`std::hash<int>{}(x)`** — правильный способ вычислить хеш.

---

## Примеры

- [map_basic.cpp](map_basic.cpp) — `map`: вставка, доступ, обход
- [map_count.cpp](map_count.cpp) — частоты слов через `map`
- [set_basic.cpp](set_basic.cpp) — `set`: уникальность, сортировка
- [set_ops.cpp](set_ops.cpp) — операции над множествами
- [unordered_basic.cpp](unordered_basic.cpp) — `unordered_map`, `unordered_set`
- [custom_hash.cpp](custom_hash.cpp) — свой хеш для `Point`

## Запуск

**CLion:** выбрать цель → **Shift+F10**.

**Терминал:**

```bash
mkdir build && cd build
cmake ..
cmake --build .
./lesson-18-associative-containers/map_basic
```

## Что дальше

Урок 19 — алгоритмы STL: `sort`, `find`, ranges, лямбды.