#include <iostream>
#include <string>
#include <charconv>
#include <expected>

// std::expected<T, E> (C++23) — альтернатива исключениям.

std::expected<int, std::string> parse_int(const std::string& s) {
    int value;
    auto [ptr, ec] = std::from_chars(s.data(), s.data() + s.size(), value);

    if (ec == std::errc()) {
        return value;
    }
    return std::unexpected("не число: \"" + s + "\"");
}

std::expected<double, std::string> safe_divide(int a, int b) {
    if (b == 0) {
        return std::unexpected("деление на ноль");
    }
    return static_cast<double>(a) / b;
}

int main() {
    std::cout << "=== parse_int ===\n";

    for (const std::string& s : {"123", "abc", "42"}) {
        auto result = parse_int(s);
        if (result) {
            std::cout << "\"" << s << "\" -> " << *result << "\n";
        } else {
            std::cout << "\"" << s << "\" -> ошибка: "
                      << result.error() << "\n";
        }
    }

    std::cout << "\n=== safe_divide ===\n";

    std::cout << "10 / 3:\n";
    if (auto r = safe_divide(10, 3); r) {
        std::cout << "  " << *r << "\n";
    } else {
        std::cout << "  " << r.error() << "\n";
    }

    std::cout << "10 / 0:\n";
    if (auto r = safe_divide(10, 0); r) {
        std::cout << "  " << *r << "\n";
    } else {
        std::cout << "  " << r.error() << "\n";
    }

    return 0;
}
