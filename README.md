# Программирование на C++

Учебный курс по программированию на C++ (стандарт **C++23**):
от первой программы до ООП, STL, умных указателей и RTTI.
Каждый урок — отдельная папка с кратким конспектом и рабочими
примерами кода.

Курс рассчитан на студентов, знакомых с основами программирования
(переменные, циклы, ветвления). Опыт C++ не требуется.

## Содержание

### Модуль 1. Основы языка

| № | Тема | Конспект | Примеры |
|---|------|----------|---------|
| 1 | Введение. Первая программа. Ввод-вывод. Память и типы данных | [README](lesson-01-intro/README.md) | [код](lesson-01-intro/) |
| 2 | Память и типы данных. IEEE 754. Битовые операции | [README](lesson-02-memory-types/README.md) | [код](lesson-02-memory-types/) |
| 3 | Условия, `switch`, циклы `while` / `for`, `break`, `continue` | [README](lesson-03-control-flow/README.md) | [код](lesson-03-control-flow/) |
| 4 | Функции. Рекурсия. Перегрузка | [README](lesson-04-functions/README.md) | [код](lesson-04-functions/) |
| 5 | Введение в указатели. Арифметика указателей | [README](lesson-05-pointers/README.md) | [код](lesson-05-pointers/) |
| 6 | Висячие указатели, утечки. Ссылки. Умные указатели (кратко) | [README](lesson-06-memory-safety/README.md) | [код](lesson-06-memory-safety/) |
| 7 | Массивы. Статические и динамические. Связь с указателями | [README](lesson-07-arrays/README.md) | [код](lesson-07-arrays/) |
| 8 | Двумерные массивы. Строки. Файлы | [README](lesson-08-2d-strings-files/README.md) | [код](lesson-08-2d-strings-files/) |
| 9 | Структуры. Введение в ООП | [README](lesson-09-structs-oop-intro/README.md) | [код](lesson-09-structs-oop-intro/) |
| 10 | Контрольная работа (демо-разбор) | [README](lesson-10-test-demo/README.md) | [код](lesson-10-test-demo/) |
| 11 | Классы: конструкторы, деструкторы, перегрузка операций | [README](lesson-11-classes/README.md) | [код](lesson-11-classes/) |
| 12 | Передача объектов в функции. Коллекции. Перегрузка операций | [README](lesson-12-objects-collections/README.md) | [код](lesson-12-objects-collections/) |
| 13 | Исключения. RAII. Правило трёх (пяти) | [README](lesson-13-exceptions-raii/README.md) | [код](lesson-13-exceptions-raii/) |
| 14 | Умные указатели: `unique_ptr`, `shared_ptr`, `weak_ptr` | [README](lesson-14-smart-pointers/README.md) | [код](lesson-14-smart-pointers/) |
| 15 | Move-семантика. `std::move`, rvalue-ссылки | [README](lesson-15-move-semantics/README.md) | [код](lesson-15-move-semantics/) |

### Модуль 2. STL и продвинутые темы

| № | Тема | Конспект | Примеры |
|---|------|----------|---------|
| 16 | Контейнеры последовательные: `vector`, `deque`, `list` | [README](lesson-16-sequence-containers/README.md) | [код](lesson-16-sequence-containers/) |
| 17 | Контейнеры последовательные: практика | [README](lesson-17-sequence-practice/README.md) | [код](lesson-17-sequence-practice/) |
| 18 | Ассоциативные контейнеры: `map`, `set`, `unordered_map` | [README](lesson-18-associative-containers/README.md) | [код](lesson-18-associative-containers/) |
| 19 | Алгоритмы STL: `sort`, `find`, ranges, лямбды | [README](lesson-19-stl-algorithms/README.md) | [код](lesson-19-stl-algorithms/) |
| 20 | Разбор демо контрольной работы | [README](lesson-20-test-demo/README.md) | [код](lesson-20-test-demo/) |
| 21 | Наследование: базовое | [README](lesson-21-inheritance-basic/README.md) | [код](lesson-21-inheritance-basic/) |
| 22 | Наследование: практика, RTTI, `static_cast` / `dynamic_cast` | [README](lesson-22-inheritance-rtti/README.md) | [код](lesson-22-inheritance-rtti/) |
| 23 | Подготовка к коллоквиуму | [README](lesson-23-colloquium-prep/README.md) | [код](lesson-23-colloquium-prep/) |
| 24 | Подготовка к коллоквиуму (продолжение) | [README](lesson-24-colloquium-prep-2/README.md) | [код](lesson-24-colloquium-prep-2/) |
| 25 | Абстрактные классы, чистые виртуальные функции | [README](lesson-25-abstract-classes/README.md) | [код](lesson-25-abstract-classes/) |
| 26 | Абстрактные классы: практика, интерфейсы | [README](lesson-26-abstract-practice/README.md) | [код](lesson-26-abstract-practice/) |
| 27 | RTTI, виды кастов: полная картина | [README](lesson-27-rtti-casts/README.md) | [код](lesson-27-rtti-casts/) |
| 28 | Разбор демо экзамена | [README](lesson-28-exam-demo/README.md) | [код](lesson-28-exam-demo/) |

### Дополнительно

| Тема | Конспект |
|---|---|
| Бонус. Типичные вопросы коллоквиума с краткими ответами | [README](bonus-colloquium-questions/README.md) |

## Среда

Курс рассчитан на **C++23** и компилятор **GCC 13+** или **Clang 16+**.
Сборка — через **CMake** (3.20+).

### Установка

**Fedora Linux:**

```bash
sudo dnf install gcc-c++ cmake ninja-build
```

Проверка:

```bash
g++ --version        # ожидается GCC 13+ (рекомендуется 14+)
cmake --version      # ожидается 3.20+
```

**Ubuntu / Debian:**

```bash
sudo apt install g++ cmake ninja-build
```

Для C++23 нужен **GCC 13+** (на Ubuntu 22.04 — из PPA или обновление
до 24.04; на Debian 12 — из backports).

**Windows:** MSYS2 с GCC 13+ (<https://www.msys2.org>)
или Visual Studio 2022 с `/std:c++latest`.

### IDE

**CLion** (<https://www.jetbrains.com/clion/>) — открывает корневой
`CMakeLists.txt` как проект, показывает все цели в выпадающем списке.

### Сборка из терминала

```bash
mkdir build && cd build
cmake ..
cmake --build .
./lesson-01-intro/hello
```

Или через CLion: выбрать цель → **Run** (Shift+F10) или **Debug** (Shift+F9).

## Структура репозитория

```
cpp-university/
├── CMakeLists.txt              корневой, подключает все уроки
├── README.md
├── LICENSE
├── .gitignore
├── lesson-01-intro/
│   ├── CMakeLists.txt          цели для примеров урока
│   ├── README.md
│   └── *.cpp
├── lesson-02-memory-types/
│   ├── CMakeLists.txt
│   ├── README.md
│   └── *.cpp
├── ...
└── bonus-colloquium-questions/
    └── README.md
```

В каждой папке урока:

- `CMakeLists.txt` — список `add_executable` для примеров.
- `README.md` — конспект: цель, ключевые понятия, примеры.
- `*.cpp` — рабочие примеры кода с комментариями.

## Как проходить курс

1. Читаем `README.md` урока.
2. Открываем примеры `*.cpp`.
3. В CLion выбираем нужную цель и запускаем (Shift+F10).
4. Меняем, экспериментируем.
5. Переходим к следующему уроку.

## Что изменено относительно исходной программы

Курс сохраняет структуру исходной программы (28 уроков, два модуля),
с небольшими правками:

- **Стандарт обновлён до C++23.** Современные вузовские программы
  переходят на C++20/C++23, и курс это отражает.
- **Урок 15** — добавлена тема **move-семантика** (не было в исходной
  программе, но критично для современного C++).
- **Урок 19** — добавлена тема **алгоритмы STL** (`sort`, `find`, ranges,
  лямбды). В исходной программе были только контейнеры.
- **Урок 22** — RTTI и касты **перенесены ближе к наследованию**.
  В исходной программе они стояли в уроке 27.
- **Урок 27** — оставлен как обобщающий по кастам.
- **Бонусный урок** — вопросы коллоквиума с ответами.

## Что из C++20 / C++23 используется в курсе

По мере уместности в примерах вводятся современные возможности:

| Возможность | Стандарт | Где |
|---|---|---|
| `std::print` / `std::println` | C++23 | уроки 1+, местами |
| `std::format` | C++20 | уроки 1+ |
| `std::span` | C++20 | уроки 7+ |
| Concepts | C++20 | шаблоны, уроки 4, 6 |
| Ranges | C++20 | урок 19 |
| `std::expected` | C++23 | урок 13 (исключения) |
| `std::string::contains` | C++23 | урок 8 |
| `std::to_underlying` | C++23 | урок 9 (enum) |
| `std::stacktrace` | C++23 | уроки 13, 27 |

Базовые примеры при этом остаются **простыми и читаемыми** — `std::cout`
и классический синтаксис не отменяются.

## Требования

- Базовые знания любого языка программирования
  (переменные, условия, циклы).
- C++23-совместимый компилятор (GCC 13+, Clang 16+, MSVC 2022+).
- CMake 3.20+.
- 2–4 часа в неделю на прохождение одного урока.

## Лицензия

MIT