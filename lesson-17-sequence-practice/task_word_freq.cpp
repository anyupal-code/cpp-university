#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

// Задача 5. Частоты слов — через vector пар.
// В уроке 18 решим через map в 3 строки.

struct WordFreq {
    std::string word;
    int count;

    bool operator<(const WordFreq& o) const {
        if (count != o.count) return count > o.count;   // по частоте (убыв.)
        return word < o.word;                            // при равенстве — по алфавиту
    }
};

int main() {
    std::string text =
        "the quick brown fox jumps over the lazy dog "
        "the fox is quick and the dog is lazy";

    std::cout << "Текст: " << text << "\n\n";

    // 1. Разбить на слова
    std::istringstream iss(text);
    std::vector<std::string> words;
    std::string w;
    while (iss >> w) {
        words.push_back(w);
    }

    std::cout << "Всего слов: " << words.size() << "\n\n";

    // 2. Подсчитать частоты (ручной способ)
    std::sort(words.begin(), words.end());

    std::vector<WordFreq> freqs;
    for (std::size_t i = 0; i < words.size(); ) {
        std::size_t j = i;
        while (j < words.size() && words[j] == words[i]) ++j;

        freqs.push_back({words[i], static_cast<int>(j - i)});
        i = j;
    }

    // 3. Сортировать по частоте
    std::sort(freqs.begin(), freqs.end());

    std::cout << "=== Частоты (по убыванию) ===\n";
    for (const auto& f : freqs) {
        std::cout << "  " << f.word << ": " << f.count << "\n";
    }

    std::cout << "\nУникальных слов: " << freqs.size() << "\n";

    return 0;
}
