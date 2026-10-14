#include <iostream>
#include <string>
#include <utility>
#include <memory>

// std::forward: perfect forwarding.

class Widget {
private:
    std::string name_;
    int value_;
public:
    Widget(std::string name, int value)
        : name_(std::move(name)), value_(value) {
        std::cout << "  Widget(" << name_ << ", " << value_ << ")\n";
    }
};

// Фабрика с perfect forwarding
template <typename T, typename... Args>
std::unique_ptr<T> make_object(Args&&... args) {
    std::cout << "  make_object вызывается\n";
    return std::make_unique<T>(std::forward<Args>(args)...);
}

// Простая функция-обёртка
void target(const std::string& s) {
    std::cout << "  target получил: \"" << s << "\"\n";
}

template <typename T>
void wrapper(T&& arg) {
    std::cout << "  wrapper получил аргумент\n";
    target(std::forward<T>(arg));
}

int main() {
    std::cout << "=== make_object ===\n";
    auto w = make_object<Widget>("Test", 42);

    std::cout << "\n=== wrapper с lvalue ===\n";
    std::string s = "Pascal";
    wrapper(s);            // lvalue

    std::cout << "\n=== wrapper с rvalue ===\n";
    wrapper(std::string("C++"));    // rvalue

    std::cout << "\n=== wrapper с литералом ===\n";
    wrapper("Go");                  // rvalue

    return 0;
}
