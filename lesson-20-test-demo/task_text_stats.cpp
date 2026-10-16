#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <cctype>

// Задача 5. Статистика текста: слова, уникальные, топ-5.

std::string normalize(std::string s) {
    // Оставляем только буквы, в нижнем регистре
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
        "The lazy dog sleeps.";

    std::cout << "Текст:\n" << text << "\n\n";

    // Разбить на слова и нормализовать
    std::istringstream iss(text);
    std::string raw_word;
    std::vector<std::string> words;

    while (iss >> raw_word) {
        std::string word = normalize(raw_word);
        if (!word.empty()) {
            words.push_back(word);
        }
    }

    std::cout << "Всего слов: " << words.size() << "\n";

    // Частоты
    std::unordered_map<std::string, int> freq;
    for (const auto& w : words) ++freq[w];

    std::cout << "Уникальных: " << freq.size() << "\n\n";

    // Топ-5 через partial_sort
    std::vector<std::pair<std::string, int>> items(freq.begin(), freq.end());

    const int K = 5;
    int k = std::min<int>(K, items.size());

    std::partial_sort(items.begin(), items.begin() + k, items.end(),
                      [](const auto& a, const auto& b) {
                          if (a.second != b.second) return a.second > b.second;
                          return a.first < b.first;
                      });

    std::cout << "=== Топ-" << k << " ===\n";
    for (int i = 0; i < k; ++i) {
        std::cout << "  " << (i + 1) << ". " << items[i].first
                  << ": " << items[i].second << "\n";
    }

    return 0;
}