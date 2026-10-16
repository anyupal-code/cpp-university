#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

// Частоты слов через map — в 3 строки.

int main() {
    std::string text =
        "the quick brown fox jumps over the lazy dog "
        "the fox is quick and the dog is lazy";

    std::cout << "Текст: " << text << "\n\n";

    // 1. Подсчёт через map — основная часть
    std::map<std::string, int> freq;
    std::istringstream iss(text);
    std::string w;
    while (iss >> w) ++freq[w];

    // 2. Вывод по алфавиту (map уже отсортирован)
    std::cout << "=== По алфавиту ===\n";
    for (const auto& [word, count] : freq) {
        std::cout << "  " << word << ": " << count << "\n";
    }

    // 3. Сортировка по частоте
    std::vector<std::pair<std::string, int>> items(freq.begin(), freq.end());
    std::sort(items.begin(), items.end(),
              [](const auto& a, const auto& b) {
                  if (a.second != b.second) return a.second > b.second;
                  return a.first < b.first;
              });

    std::cout << "\n=== По частоте (убывание) ===\n";
    for (const auto& [word, count] : items) {
        std::cout << "  " << word << ": " << count << "\n";
    }

    std::cout << "\nУникальных слов: " << freq.size() << "\n";

    return 0;
}