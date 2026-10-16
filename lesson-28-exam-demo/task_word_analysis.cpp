#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <set>
#include <vector>
#include <algorithm>
#include <cctype>

// Задача 1. Анализ текста.

std::string normalize(std::string s) {
    std::string result;
    for (char c : s) {
        if (std::isalpha(static_cast<unsigned char>(c))) {
            result += std::tolower(static_cast<unsigned char>(c));
        }
    }
    return result;
}

int main() {
    std::string text =
        "The quick brown fox jumps over the lazy dog. "
        "The dog barks, and the fox runs away. "
        "The lazy dog sleeps. A cat watches the fox.";

    std::cout << "Текст:\n" << text << "\n\n";

    // Разбить на слова и нормализовать
    std::istringstream iss(text);
    std::vector<std::string> words;
    std::string raw;

    while (iss >> raw) {
        std::string w = normalize(raw);
        if (!w.empty()) words.push_back(w);
    }

    // Частоты
    std::unordered_map<std::string, int> freq;
    for (const auto& w : words) ++freq[w];

    std::cout << "Всего слов: " << words.size() << "\n";
    std::cout << "Уникальных: " << freq.size() << "\n\n";

    // Топ-5
    std::vector<std::pair<std::string, int>> items(freq.begin(), freq.end());
    int k = std::min<int>(5, items.size());
    std::partial_sort(items.begin(), items.begin() + k, items.end(),
                      [](const auto& a, const auto& b) {
                          if (a.second != b.second) return a.second > b.second;
                          return a.first < b.first;
                      });

    std::cout << "=== Топ-5 ===\n";
    for (int i = 0; i < k; ++i) {
        std::cout << "  " << (i + 1) << ". " << items[i].first
                  << ": " << items[i].second << "\n";
    }

    // Слова, встречающиеся один раз
    std::set<std::string> unique_once;
    for (const auto& [w, c] : freq) {
        if (c == 1) unique_once.insert(w);
    }

    std::cout << "\n=== Встречаются один раз (" << unique_once.size() << ") ===\n";
    for (const auto& w : unique_once) {
        std::cout << "  " << w << "\n";
    }

    // Самая длинная цепочка слов, начинающихся с одной буквы
    std::cout << "\n=== Цепочки по первой букве ===\n";
    std::unordered_map<char, int> letter_count;
    for (const auto& w : words) {
        if (!w.empty()) ++letter_count[w[0]];
    }

    char best_letter = 0;
    int best_count = 0;
    for (const auto& [letter, count] : letter_count) {
        if (count > best_count) {
            best_count = count;
            best_letter = letter;
        }
    }

    std::cout << "  Самая частая первая буква: '" << best_letter
              << "' (" << best_count << " слов)\n";

    return 0;
}