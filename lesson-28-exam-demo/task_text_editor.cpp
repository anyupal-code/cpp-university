#include <iostream>
#include <string>
#include <stack>
#include <vector>

// Задача 4. Текстовый редактор с undo/redo.

class TextEditor {
    std::string text_;
    std::stack<std::string> undo_stack_;
    std::stack<std::string> redo_stack_;
    static constexpr std::size_t MAX_HISTORY = 100;

    void trim_undo() {
        // Ограничение истории: при переполнении удаляем самые старые
        // std::stack не даёт удалить снизу, поэтому используем vector для
        // настоящей реализации — здесь упрощённо игнорируем.
    }

public:
    void insert(const std::string& s) {
        undo_stack_.push(text_);
        text_ += s;
        while (!redo_stack_.empty()) redo_stack_.pop();   // сброс redo

        // Ограничение истории
        if (undo_stack_.size() > MAX_HISTORY) {
            // Упрощение: чистим всю историю, если стало слишком много
            // В реальном коде — используем deque
            while (undo_stack_.size() > MAX_HISTORY) {
                std::stack<std::string> temp;
                while (undo_stack_.size() > 1) {
                    temp.push(undo_stack_.top());
                    undo_stack_.pop();
                }
                undo_stack_.pop();
                while (!temp.empty()) {
                    undo_stack_.push(temp.top());
                    temp.pop();
                }
            }
        }
    }

    bool undo() {
        if (undo_stack_.empty()) return false;
        redo_stack_.push(text_);
        text_ = undo_stack_.top();
        undo_stack_.pop();
        return true;
    }

    bool redo() {
        if (redo_stack_.empty()) return false;
        undo_stack_.push(text_);
        text_ = redo_stack_.top();
        redo_stack_.pop();
        return true;
    }

    void clear() {
        undo_stack_.push(text_);
        text_.clear();
        while (!redo_stack_.empty()) redo_stack_.pop();
    }

    const std::string& text() const { return text_; }

    std::size_t undo_size() const { return undo_stack_.size(); }
    std::size_t redo_size() const { return redo_stack_.size(); }
};

int main() {
    TextEditor editor;

    std::cout << "=== Ввод ===\n";
    editor.insert("Hello");
    std::cout << "После insert(\"Hello\"): \"" << editor.text() << "\"\n";

    editor.insert(", World");
    std::cout << "После insert(\", World\"): \"" << editor.text() << "\"\n";

    editor.insert("!");
    std::cout << "После insert(\"!\"): \"" << editor.text() << "\"\n";

    std::cout << "\nИстория undo: " << editor.undo_size() << "\n";

    std::cout << "\n=== Undo ===\n";
    editor.undo();
    std::cout << "После undo: \"" << editor.text() << "\"\n";

    editor.undo();
    std::cout << "После undo: \"" << editor.text() << "\"\n";

    editor.undo();
    std::cout << "После undo: \"" << editor.text() << "\"\n";

    editor.undo();   // ничего не осталось
    std::cout << "После undo (пусто): \"" << editor.text() << "\"\n";

    std::cout << "\n=== Redo ===\n";
    editor.redo();
    std::cout << "После redo: \"" << editor.text() << "\"\n";

    editor.redo();
    std::cout << "После redo: \"" << editor.text() << "\"\n";

    editor.redo();
    std::cout << "После redo: \"" << editor.text() << "\"\n";

    std::cout << "\n=== Новый ввод сбрасывает redo ===\n";
    editor.undo();
    editor.insert("?");
    std::cout << "После undo + insert(\"?\"): \"" << editor.text() << "\"\n";
    std::cout << "Redo пуст: " << (editor.redo_size() == 0) << "\n";

    return 0;
}