#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

// Задача 2. Группировка слов по длине.

int main() {
    std::string text =
        "the quick brown fox jumps over the lazy dog "
        "a an cat dog elephant bird fox";

    std::cout << "Текст: " << text << "\n\n";

    // Разбить на слова
    std::istringstream iss(text);
    std::vector<std::string> words;
    std::string w;
    while (iss >> w) words.push_back(w);

    // Сгруппировать по длине
    std::map<std::size_t, std::vector<std::string>> groups;
    for (const auto& word : words) {
        groups[word.size()].push_back(word);
    }

    // Внутри группы: сортировка + уникальные
    for (auto& [length, group] : groups) {
        std::sort(group.begin(), group.end());
        group.erase(std::unique(group.begin(), group.end()), group.end());
    }

    // Вывод
    std::cout << "=== Группы по длине ===\n";
    for (const auto& [length, group] : groups) {
        std::cout << length << " букв: ";
        for (const auto& word : group) {
            std::cout << word << " ";
        }
        std::cout << "\n";
    }

    return 0;
}