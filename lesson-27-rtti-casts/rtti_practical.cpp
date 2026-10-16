#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <typeinfo>

// Практическое применение RTTI.

class Event {
public:
    virtual ~Event() = default;
    virtual std::string type() const = 0;
};

class ClickEvent : public Event {
public:
    int x_, y_;
    ClickEvent(int x, int y) : x_(x), y_(y) {}
    std::string type() const override { return "click"; }
};

class KeyEvent : public Event {
public:
    char key_;
    explicit KeyEvent(char k) : key_(k) {}
    std::string type() const override { return "key"; }
};

class ResizeEvent : public Event {
public:
    int w_, h_;
    ResizeEvent(int w, int h) : w_(w), h_(h) {}
    std::string type() const override { return "resize"; }
};

// Обработка через dynamic_cast
void process_dynamic(Event& e) {
    if (auto* click = dynamic_cast<ClickEvent*>(&e)) {
        std::cout << "  Клик в (" << click->x_ << ", " << click->y_ << ")\n";
    } else if (auto* key = dynamic_cast<KeyEvent*>(&e)) {
        std::cout << "  Клавиша: '" << key->key_ << "'\n";
    } else if (auto* resize = dynamic_cast<ResizeEvent*>(&e)) {
        std::cout << "  Изменение размера: " << resize->w_
                  << "x" << resize->h_ << "\n";
    } else {
        std::cout << "  Неизвестное событие\n";
    }
}

// Обработка через typeid
void process_typeid(Event& e) {
    if (typeid(e) == typeid(ClickEvent)) {
        auto& click = static_cast<ClickEvent&>(e);
        std::cout << "  (typeid) Клик в (" << click.x_ << ", " << click.y_ << ")\n";
    } else if (typeid(e) == typeid(KeyEvent)) {
        auto& key = static_cast<KeyEvent&>(e);
        std::cout << "  (typeid) Клавиша: '" << key.key_ << "'\n";
    }
}

int main() {
    std::vector<std::unique_ptr<Event>> events;
    events.push_back(std::make_unique<ClickEvent>(100, 200));
    events.push_back(std::make_unique<KeyEvent>('A'));
    events.push_back(std::make_unique<ResizeEvent>(800, 600));
    events.push_back(std::make_unique<ClickEvent>(50, 50));

    std::cout << "=== Через dynamic_cast ===\n";
    for (auto& e : events) {
        std::cout << e->type() << ":\n";
        process_dynamic(*e);
    }

    std::cout << "\n=== Через typeid ===\n";
    for (auto& e : events) {
        process_typeid(*e);
    }

    std::cout << "\n=== Сравнение подходов ===\n";
    std::cout << "  virtual type() — самый быстрый, рекомендуемый\n";
    std::cout << "  dynamic_cast — проверка «является ли», работает с наследованием\n";
    std::cout << "  typeid — точное совпадение, для наследников не сработает\n";

    return 0;
}