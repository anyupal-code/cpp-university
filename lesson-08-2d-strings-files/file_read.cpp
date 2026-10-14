#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

// Чтение из файла через std::ifstream.

int main() {
    std::ifstream fin("output.txt");

    if (!fin) {
        std::cerr << "Файл не найден. Сначала запустите file_write.\n";
        return 1;
    }

    std::cout << "=== Чтение построчно ===\n";
    std::string line;
    int line_num = 1;
    while (std::getline(fin, line)) {
        std::cout << line_num++ << ": " << line << "\n";
    }

    fin.close();

    // Повторное открытие — читаем числа
    std::cout << "\n=== Чтение чисел ===\n";
    fin.open("output.txt");

    std::string word;
    int count = 0;
    while (fin >> word) {
        ++count;
    }
    std::cout << "Слов/чисел в файле: " << count << "\n";

    // Разбиение строки через istringstream
    std::cout << "\n=== Парсинг строки ===\n";
    std::string data = "10 20 30 40 50";
    std::istringstream iss(data);
    int x, sum = 0;
    while (iss >> x) {
        sum += x;
    }
    std::cout << "Сумма чисел \"" << data << "\" = " << sum << "\n";

    return 0;
}