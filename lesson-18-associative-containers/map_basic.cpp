#include <iostream>
#include <map>
#include <string>

// map: упорядоченный словарь.

int main() {
    std::map<std::string, int> ages;

    // Вставка разными способами
    ages["Иван"] = 25;
    ages["Мария"] = 30;
    ages.insert({"Пётр", 28});
    ages.emplace("Олег", 22);
    ages["Анна"] = 27;

    std::cout << "Размер: " << ages.size() << "\n\n";

    // Обход — порядок по алфавиту
    std::cout << "=== Все записи (отсортированы) ===\n";
    for (const auto& [name, age] : ages) {
        std::cout << "  " << name << ": " << age << "\n";
    }

    // Доступ
    std::cout << "\n=== Доступ ===\n";
    std::cout << "ages[\"Иван\"] = " << ages["Иван"] << "\n";
    std::cout << "ages.at(\"Мария\") = " << ages.at("Мария") << "\n";

    // Обновление
    ages["Иван"] = 26;
    std::cout << "После обновления Иван: " << ages["Иван"] << "\n";

    // Проверка наличия
    std::cout << "\n=== Проверка ===\n";
    std::cout << "contains(\"Пётр\")? " << ages.contains("Пётр") << "\n";
    std::cout << "contains(\"Сергей\")? " << ages.contains("Сергей") << "\n";

    auto it = ages.find("Мария");
    if (it != ages.end()) {
        std::cout << "Найдено: " << it->first << " -> " << it->second << "\n";
    }

    // Удаление
    ages.erase("Олег");
    std::cout << "\nПосле erase(\"Олег\"): размер = " << ages.size() << "\n";

    // ОПАСНО: [] создаёт элемент
    std::cout << "\nages[\"Новый\"] = " << ages["Новый"]
              << " (создан по умолчанию)\n";
    std::cout << "Размер после: " << ages.size() << "\n";

    return 0;
}