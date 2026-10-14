#include <iostream>
#include <deque>
#include <string>

// Задача 2. Стек отмен с ограничением на размер.

class UndoStack {
private:
    std::deque<std::string> actions_;
    std::size_t max_size_;

public:
    explicit UndoStack(std::size_t max) : max_size_(max) {}

    void push(const std::string& action) {
        actions_.push_back(action);
        if (actions_.size() > max_size_) {
            actions_.pop_front();   // вытесняем самое старое
        }
        std::cout << "  push: " << action << "\n";
    }

    std::string undo() {
        if (actions_.empty()) return "(нет действий)";
        std::string last = actions_.back();
        actions_.pop_back();
        return last;
    }

    void print() const {
        std::cout << "  стек: [";
        for (std::size_t i = 0; i < actions_.size(); ++i) {
            std::cout << "\"" << actions_[i] << "\"";
            if (i + 1 < actions_.size()) std::cout << ", ";
        }
        std::cout << "]\n";
    }
};

int main() {
    UndoStack stack(3);

    std::cout << "Стек на 3 действия\n\n";

    stack.push("открыть файл");
    stack.print();

    stack.push("изменить строку 1");
    stack.print();

    stack.push("удалить строку 2");
    stack.print();

    std::cout << "\nДобавляем четвёртое — вытесняет первое:\n";
    stack.push("сохранить");
    stack.print();

    std::cout << "\n=== Undo ===\n";
    for (int i = 0; i < 4; ++i) {
        std::cout << "undo -> " << stack.undo() << "\n";
        stack.print();
    }

    return 0;
}
