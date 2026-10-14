# Урок 8. Двумерные массивы. Строки. Файлы

## Цель

Освоить работу с матрицами, строками `std::string` и файловым
вводом-выводом через `fstream`.

## Ключевые понятия

- **Двумерный массив** — массив массивов, доступ через `m[i][j]`.
- **Матрица** — частный случай: `N × M`.
- **`std::string`** — строка STL, безопасная и удобная.
- **`std::ifstream` / `std::ofstream`** — файловые потоки.
- **`std::getline`** — чтение строки целиком.

---

## 1. Двумерные массивы

```cpp
int m[3][4];               // 3 строки × 4 столбца
int a[2][3] = {
    {1, 2, 3},
    {4, 5, 6}
};
```

- Первый индекс — **строка**.
- Второй — **столбец**.
- Доступ: `m[i][j]`.

**Размер:**

```cpp
std::size_t rows = sizeof(m) / sizeof(m[0]);        // 3
std::size_t cols = sizeof(m[0]) / sizeof(m[0][0]);  // 4
```

### Ввод / вывод матрицы

```cpp
for (int i = 0; i < rows; ++i)
    for (int j = 0; j < cols; ++j)
        std::cin >> m[i][j];

for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j)
        std::cout << m[i][j] << " ";
    std::cout << "\n";
}
```

---

## 2. `std::vector<std::vector<int>>` — динамическая матрица

Для матриц **произвольного размера**:

```cpp
#include <vector>

int n, m;
std::cin >> n >> m;

// n строк, в каждой m элементов
std::vector<std::vector<int>> mat(n, std::vector<int>(m));
```

- `mat.size()` — число строк.
- `mat[i].size()` — число элементов в i-й строке.

**Доступ:** `mat[i][j]`.

**Преимущества:**

- Размер задаётся во время выполнения.
- Память освобождается автоматически.

---

## 3. Типичные операции с матрицами

### Сумма всех элементов

```cpp
int sum = 0;
for (const auto& row : mat)
    for (int x : row)
        sum += x;
```

### Главная диагональ (квадратная матрица)

```cpp
int n = mat.size();
int diag = 0;
for (int i = 0; i < n; ++i)
    diag += mat[i][i];
```

### Побочная диагональ

```cpp
for (int i = 0; i < n; ++i)
    diag += mat[i][n - 1 - i];
```

### Транспонирование

```cpp
std::vector<std::vector<int>> t(m, std::vector<int>(n));
for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
        t[j][i] = mat[i][j];
```

### Умножение матриц

```cpp
std::vector<std::vector<int>> c(n, std::vector<int>(p, 0));
for (int i = 0; i < n; ++i)
    for (int j = 0; j < p; ++j)
        for (int k = 0; k < m; ++k)
            c[i][j] += a[i][k] * b[k][j];
```

---

## 4. `std::string`

**Строка STL** — основной инструмент работы с текстом.

```cpp
#include <string>

std::string s = "Hello";
std::string t{"World"};
std::string u(5, 'x');   // "xxxxx"
```

### Операции

| Что | Как |
|---|---|
| Конкатенация | `s + t`, `s += t` |
| Длина | `s.size()`, `s.length()` |
| Пустая? | `s.empty()` |
| Доступ к символу | `s[i]`, `s.at(i)` |
| Подстрока | `s.substr(pos, len)` |
| Поиск | `s.find("sub")` |
| Вставка | `s.insert(pos, "text")` |
| Удаление | `s.erase(pos, len)` |
| Замена | `s.replace(pos, len, "new")` |
| Очистка | `s.clear()` |
| Проверка подстроки (C++23) | `s.contains("sub")` |

### Примеры

```cpp
std::string s = "Hello, World!";

std::cout << s.size() << "\n";              // 13
std::cout << s.substr(0, 5) << "\n";        // "Hello"
std::cout << s.find("World") << "\n";       // 7
std::cout << s[0] << "\n";                  // 'H'

s += "!!!";                                 // "Hello, World!!!"
s.replace(0, 5, "Hi");                      // "Hi, World!!!"
```

### Обход

```cpp
for (char c : s) {
    std::cout << c << " ";
}
```

### Изменение регистра

```cpp
#include <cctype>

for (char& c : s) c = std::toupper(c);
```

### C++23: `contains`

```cpp
if (s.contains("World")) {
    std::cout << "Содержит 'World'\n";
}
```

Раньше было: `s.find("World") != std::string::npos`.

### Преобразование чисел

```cpp
std::string s = std::to_string(42);       // "42"
int n = std::stoi("123");                  // 123
double d = std::stod("3.14");              // 3.14
```

- `std::stoi`, `std::stol`, `std::stoll` — целые.
- `std::stof`, `std::stod` — вещественные.

### Ввод строки

```cpp
std::string s;
std::getline(std::cin, s);    // читает всю строку до Enter
```

**Важно:** если перед этим был `std::cin >> x`, нужен `std::cin.ignore()`.

---

## 5. Файловый ввод-вывод

### `std::ofstream` — запись

```cpp
#include <fstream>

std::ofstream fout("output.txt");

if (!fout) {
    std::cerr << "Не удалось открыть файл\n";
    return 1;
}

fout << "Hello, file!\n";
fout << 42 << " " << 3.14 << "\n";

// Файл закроется автоматически (RAII)
```

### `std::ifstream` — чтение

```cpp
std::ifstream fin("input.txt");

if (!fin) {
    std::cerr << "Файл не найден\n";
    return 1;
}

int x;
while (fin >> x) {          // читаем числа до конца
    std::cout << x << " ";
}
```

**Построчно:**

```cpp
std::string line;
while (std::getline(fin, line)) {
    std::cout << line << "\n";
}
```

### Дозапись в конец

```cpp
std::ofstream fout("log.txt", std::ios::app);
fout << "Новая строка\n";
```

### Режимы открытия

| Флаг | Что делает |
|---|---|
| `std::ios::in` | чтение |
| `std::ios::out` | запись (перезапись) |
| `std::ios::app` | дозапись в конец |
| `std::ios::binary` | бинарный режим |

---

## 6. Типичные задачи

### Сумма чисел из файла

```cpp
std::ifstream fin("nums.txt");
int x, sum = 0;
while (fin >> x) sum += x;
std::cout << sum << "\n";
```

### Копирование файла

```cpp
std::ifstream fin("in.txt");
std::ofstream fout("out.txt");
std::string line;
while (std::getline(fin, line)) {
    fout << line << "\n";
}
```

### Подсчёт слов

```cpp
std::ifstream fin("text.txt");
std::string word;
int count = 0;
while (fin >> word) ++count;
std::cout << "Слов: " << count << "\n";
```

### Разбиение строки

```cpp
std::string s = "10 20 30 40";
std::istringstream iss(s);
int x;
while (iss >> x) {
    std::cout << x * 2 << " ";
}
```

`std::istringstream` — поток из строки, удобно для парсинга.

---

## 7. Частые ошибки

- **Путаница индексов** в матрице: `m[i][j]` — строка, столбец.
- **Выход за границы** — `m[n]` вместо `m[n-1]`.
- **`std::cin >> s`** читает только до пробела. Для строки целиком — `std::getline`.
- **Забыли `std::cin.ignore()`** перед `getline` — получаете пустую строку.
- **Не проверили открытие файла** — программа упадёт при отсутствии.
- **`std::stoi("abc")`** — исключение `std::invalid_argument`. Проверяйте.
- **Файл не закрыт** — в современном C++ RAII закрывает автоматически,
  но если работаете через `.open()` / `.close()` — не забудьте.
- **Смешивание C-строк и `std::string`** — работает, но осторожно.

---

## Примеры

- [matrix_basic.cpp](matrix_basic.cpp) — объявление, ввод, вывод матрицы
- [matrix_algorithms.cpp](matrix_algorithms.cpp) — сумма, диагонали, транспонирование
- [string_basic.cpp](string_basic.cpp) — создание, длина, обход, конкатенация
- [string_ops.cpp](string_ops.cpp) — `find`, `substr`, `replace`, `contains`
- [file_write.cpp](file_write.cpp) — запись в файл
- [file_read.cpp](file_read.cpp) — чтение из файла

## Запуск

**CLion:** выбрать цель → **Shift+F10**.

**Терминал:**

```bash
mkdir build && cd build
cmake ..
cmake --build .
./lesson-08-2d-strings-files/matrix_basic
```

## Что дальше

Урок 9 — структуры, введение в ООП.