#include <iostream>
#include <vector>
#include <fstream>

// RAII: деструктор вызывается даже при исключении.

class Resource {
private:
    std::string name_;
public:
    explicit Resource(const std::string& n) : name_(n) {
        std::cout << "  Ресурс '" << name_ << "' создан\n";
    }

    ~Resource() {
        std::cout << "  Ресурс '" << name_ << "' уничтожен\n";
    }
};

void throw_demo() {
    Resource r1("A");
    Resource r2("B");

    std::cout << "  Бросаем исключение...\n";
    throw std::runtime_error("что-то пошло не так");

    // Эта строка не выполнится
    Resource r3("C");
}

int main() {
    std::cout << "=== Без исключения ===\n";
    {
        Resource r("main");
        std::cout << "  Работаем с ресурсом\n";
    }

    std::cout << "\n=== С исключением ===\n";
    try {
        throw_demo();
    } catch (const std::exception& e) {
        std::cout << "Поймано: " << e.what() << "\n";
    }

    std::cout << "\n=== RAII с файлом ===\n";
    try {
        std::ofstream fout("raii_test.txt");
        fout << "Данные\n";
        throw std::runtime_error("ошибка");
        // fout закроется автоматически
    } catch (const std::exception& e) {
        std::cout << "Поймано: " << e.what() << "\n";
        std::cout << "(файл всё равно закрыт)\n";
    }

    return 0;
}
