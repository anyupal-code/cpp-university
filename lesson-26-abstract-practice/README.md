# Урок 26. Абстрактные классы: практика, интерфейсы

## Цель

Освоить множественное наследование интерфейсов, паттерны на абстрактных
классах: плагины, цепочки обработчиков, «сравнимые» объекты.

## Ключевые понятия

- **Множественное наследование интерфейсов** — класс реализует
  несколько интерфейсов.
- **Плагин** — внешний класс, реализующий общий интерфейс.
- **Chain of Responsibility** — цепочка обработчиков.
- **Сравнимые объекты** — интерфейс с `compare`.
- **Чистый виртуальный деструктор** — `virtual ~T() = 0;` (с телом).

---

## 1. Множественное наследование интерфейсов

**Обычные классы — только одиночное** наследование.
**Интерфейсы (абстрактные классы без полей) — сколько угодно.**

```cpp
class IPrintable {
public:
    virtual ~IPrintable() = default;
    virtual void print() const = 0;
};

class ISerializable {
public:
    virtual ~ISerializable() = default;
    virtual std::string serialize() const = 0;
};

class IComparable {
public:
    virtual ~IComparable() = default;
    virtual int compare(const IComparable& o) const = 0;
};

// Один класс — три интерфейса
class Person : public IPrintable, public ISerializable {
    std::string name_;
    int age_;
public:
    Person(std::string name, int age)
        : name_(std::move(name)), age_(age) {}

    void print() const override;
    std::string serialize() const override;
};
```

**Что важно:**

- Каждый интерфейс — **виртуальный деструктор**.
- Каждый метод — **чистая виртуальная функция**.
- **Никаких полей** в интерфейсах.

**Порядок базовых классов:**

```cpp
class Person : public IPrintable, public ISerializable {};   // ок
```

---

## 2. Плагин-система

**Идея:** основной код знает только интерфейс. Плагины — отдельные
классы, реализующие интерфейс.

```cpp
class IPlugin {
public:
    virtual ~IPlugin() = default;
    virtual std::string name() const = 0;
    virtual void execute() = 0;
};

class LogPlugin : public IPlugin {
public:
    std::string name() const override { return "LogPlugin"; }
    void execute() override {
        std::cout << "  логирование\n";
    }
};

class BackupPlugin : public IPlugin {
public:
    std::string name() const override { return "BackupPlugin"; }
    void execute() override {
        std::cout << "  резервное копирование\n";
    }
};

// Основной код
class PluginManager {
    std::vector<std::unique_ptr<IPlugin>> plugins_;
public:
    void add(std::unique_ptr<IPlugin> p) {
        plugins_.push_back(std::move(p));
    }

    void run_all() {
        for (auto& p : plugins_) {
            std::cout << p->name() << ":\n";
            p->execute();
        }
    }
};
```

**Что даёт:**

- Добавление нового плагина **не меняет** основной код.
- Каждый плагин — изолирован.
- Тестирование по отдельности.

---

## 3. Chain of Responsibility

**Идея:** запрос передаётся по цепочке обработчиков. Каждый решает:
обработать, передать дальше или остановить.

```cpp
class Handler {
protected:
    std::shared_ptr<Handler> next_;
public:
    virtual ~Handler() = default;

    void set_next(std::shared_ptr<Handler> next) {
        next_ = std::move(next);
    }

    virtual bool handle(int request) = 0;   // true = обработано
};

class ConcreteHandler : public Handler {
    int min_, max_;
public:
    ConcreteHandler(int min, int max) : min_(min), max_(max) {}

    bool handle(int request) override {
        if (request >= min_ && request <= max_) {
            std::cout << "  Обработан в диапазоне [" << min_ << ", " << max_ << "]: "
                      << request << "\n";
            return true;
        }
        if (next_) return next_->handle(request);
        return false;
    }
};
```

**Применение:**

- Обработка событий в GUI.
- Middleware в веб-фреймворках.
- Валидация форм.

---

## 4. Сравнимые объекты — интерфейс `IComparable`

```cpp
class IComparable {
public:
    virtual ~IComparable() = default;
    virtual int compare(const IComparable& o) const = 0;
};
```

**Реализация:**

```cpp
class Person : public IComparable {
    std::string name_;
    int age_;
public:
    int compare(const IComparable& o) const override {
        const auto* other = dynamic_cast<const Person*>(&o);
        if (!other) throw std::invalid_argument("тип");

        if (age_ != other->age_) return age_ - other->age_;
        return name_.compare(other->name_);
    }
};
```

**Использование:**

```cpp
std::vector<Person> people = {...};
std::sort(people.begin(), people.end(),
          [](const Person& a, const Person& b) {
              return a.compare(b) < 0;
          });
```

**Сравнение с `operator<`:**

- `operator<` — короче, типобезопасно.
- Интерфейс `IComparable` — позволяет сравнивать объекты **разных типов**
  через общий указатель.

**В современном C++** предпочитают `operator<=>` (урок 12).

---

## 5. Чистый виртуальный деструктор

Иногда хочется сделать класс абстрактным **без** чистых виртуальных
методов — только через деструктор.

```cpp
class AbstractBase {
public:
    virtual ~AbstractBase() = 0;   // чистый виртуальный
};

AbstractBase::~AbstractBase() = default;   // ОБЯЗАТЕЛЬНО тело

class Derived : public AbstractBase {
public:
    ~Derived() override = default;
};
```

**Почему тело обязательно:**

- При уничтожении наследника **вызовется деструктор базы**.
- Без тела — ошибка линковки.

**Когда использовать:**

- Базовый класс без своих методов, но не должен создаваться.
- Улучшает читаемость — сразу видно, что класс абстрактный.

**Современный стиль:** предпочитают `virtual ~Base() = default;` + хотя бы
один чисто виртуальный метод. Но `= 0` на деструкторе тоже встречается.

---

## 6. Типичные задачи

### Множественные интерфейсы

```cpp
class IPrintable { virtual void print() const = 0; };
class ISerializable { virtual std::string serialize() const = 0; };
class ICloneable { virtual std::unique_ptr<ICloneable> clone() const = 0; };

class Document : public IPrintable, public ISerializable {
    // реализует оба
};
```

### Интерфейс + базовый класс с данными

```cpp
class Entity {                // базовый с полем
protected:
    int id_;
public:
    explicit Entity(int id) : id_(id) {}
    virtual ~Entity() = default;
    int id() const { return id_; }
};

class ISerializable {         // интерфейс
public:
    virtual ~ISerializable() = default;
    virtual std::string serialize() const = 0;
};

class User : public Entity, public ISerializable {
    std::string name_;
public:
    User(int id, std::string name) : Entity(id), name_(std::move(name)) {}

    std::string serialize() const override {
        return std::to_string(id_) + ":" + name_;
    }
};
```

**Порядок:** обычный класс — **первым**, интерфейсы — следом.

### Полиморфизм через два интерфейса

```cpp
std::vector<std::unique_ptr<IPrintable>> to_print;
std::vector<std::unique_ptr<ISerializable>> to_save;

// Один объект может быть в обоих, но через разные интерфейсы
auto user = std::make_shared<User>(1, "Иван");
```

---

## 7. Частые ошибки

- **Поля в интерфейсе** — нельзя. Интерфейс = только чистые виртуальные.
- **Не виртуальный деструктор в интерфейсе** — утечка.
- **Порядок наследования** — обычный класс **первым**, интерфейсы позже.
- **`dynamic_cast` без `virtual`** — ошибка компиляции.
- **Чистый виртуальный деструктор без тела** — ошибка линковки.
- **Ромбовидное наследование** — если два интерфейса наследуют общий,
  нужен `virtual` наследование (редко в учебном коде).
- **Срезка при передаче по значению** — теряется полиморфизм.

---

## Примеры

- [multi_interface.cpp](multi_interface.cpp) — два интерфейса у класса
- [plugin_system.cpp](plugin_system.cpp) — плагины через интерфейс
- [drawable_demo.cpp](drawable_demo.cpp) — интерфейс `IDrawable`
- [chain_handlers.cpp](chain_handlers.cpp) — цепочка обработчиков
- [comparable_demo.cpp](comparable_demo.cpp) — интерфейс `IComparable`
- [pure_virtual_destructor.cpp](pure_virtual_destructor.cpp) — чистый виртуальный деструктор

## Запуск

**CLion:** выбрать цель → **Shift+F10**.

**Терминал:**

```bash
mkdir build && cd build
cmake ..
cmake --build .
./lesson-26-abstract-practice/multi_interface
```

## Что дальше

Урок 27 — RTTI, виды кастов: полная картина.