#include <iostream>
#include <fstream>
#include <string>

// Запись в файл через std::ofstream.

int main() {
    std::ofstream fout("output.txt");

    if (!fout) {
        std::cerr << "Не удалось открыть файл для записи\n";
        return 1;
    }

    fout << "Hello, file!\n";
    fout << "Строка 2\n";

    for (int i = 1; i <= 5; ++i) {
        fout << "Число: " << i * 10 << "\n";
    }

    fout << "Числа в строку: ";
    for (int i = 1; i <= 5; ++i) {
        fout << i << " ";
    }
    fout << "\n";

    // Файл закроется автоматически (RAII)
    std::cout << "Файл output.txt создан\n";

    // Дозапись
    std::ofstream fapp("output.txt", std::ios::app);
    fapp << "Дописано в конец\n";
    std::cout << "Дописано\n";

    return 0;
}