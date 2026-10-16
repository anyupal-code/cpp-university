#include <iostream>
#include <memory>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>

// Задача 5. Библиотека.

class Book {
public:
    std::string title;
    std::string author;
    int year;
    std::string isbn;

    Book(std::string t, std::string a, int y, std::string i)
        : title(std::move(t)), author(std::move(a)),
          year(y), isbn(std::move(i)) {}

    void print() const {
        std::cout << "  \"" << std::setw(20) << std::left << title << "\""
                  << " | " << std::setw(15) << author
                  << " | " << year
                  << " | ISBN: " << isbn << "\n";
    }
};

class Library {
    std::vector<std::unique_ptr<Book>> books_;
    std::unordered_map<std::string, Book*> by_isbn_;   // индекс

public:
    void add_book(std::unique_ptr<Book> book) {
        by_isbn_[book->isbn] = book.get();
        books_.push_back(std::move(book));
    }

    std::vector<const Book*> find_by_author(const std::string& author) const {
        std::vector<const Book*> result;
        for (const auto& b : books_) {
            if (b->author == author) result.push_back(b.get());
        }
        return result;
    }

    std::vector<const Book*> find_by_year_range(int from, int to) const {
        std::vector<const Book*> result;
        for (const auto& b : books_) {
            if (b->year >= from && b->year <= to) result.push_back(b.get());
        }
        return result;
    }

    bool remove_by_isbn(const std::string& isbn) {
        auto it = std::find_if(books_.begin(), books_.end(),
                               [&](const auto& b) { return b->isbn == isbn; });
        if (it == books_.end()) return false;

        by_isbn_.erase(isbn);
        books_.erase(it);
        return true;
    }

    void sort_by_title() {
        std::sort(books_.begin(), books_.end(),
                  [](const auto& a, const auto& b) {
                      return a->title < b->title;
                  });
    }

    std::size_t total() const { return books_.size(); }

    void print_all() const {
        for (const auto& b : books_) b->print();
    }

    void save_to_file(const std::string& filename) const {
        std::ofstream fout(filename);
        for (const auto& b : books_) {
            fout << b->title << ";" << b->author << ";"
                 << b->year << ";" << b->isbn << "\n";
        }
    }

    void load_from_file(const std::string& filename) {
        std::ifstream fin(filename);
        if (!fin) return;

        std::string line;
        while (std::getline(fin, line)) {
            std::istringstream iss(line);
            std::string t, a, y_str, isbn;
            std::getline(iss, t, ';');
            std::getline(iss, a, ';');
            std::getline(iss, y_str, ';');
            std::getline(iss, isbn, ';');

            if (!t.empty()) {
                add_book(std::make_unique<Book>(t, a, std::stoi(y_str), isbn));
            }
        }
    }
};

int main() {
    Library lib;

    lib.add_book(std::make_unique<Book>("Pascal для всех", "Виpт", 1975, "ISBN001"));
    lib.add_book(std::make_unique<Book>("C++ Primer", "Lippman", 2012, "ISBN002"));
    lib.add_book(std::make_unique<Book>("Effective C++", "Meyers", 2005, "ISBN003"));
    lib.add_book(std::make_unique<Book>("The Go Programming Language", "Donovan", 2015, "ISBN004"));
    lib.add_book(std::make_unique<Book>("C++ Primer", "Lippman", 2012, "ISBN005"));

    std::cout << "Всего книг: " << lib.total() << "\n\n";

    std::cout << "=== Все книги ===\n";
    lib.print_all();

    std::cout << "\n=== Книги Lippman ===\n";
    for (const auto* b : lib.find_by_author("Lippman")) {
        b->print();
    }

    std::cout << "\n=== Книги 2005-2015 ===\n";
    for (const auto* b : lib.find_by_year_range(2005, 2015)) {
        b->print();
    }

    std::cout << "\n=== Сортировка по названию ===\n";
    lib.sort_by_title();
    lib.print_all();

    std::cout << "\n=== Удаление ISBN002 ===\n";
    lib.remove_by_isbn("ISBN002");
    std::cout << "Всего книг после удаления: " << lib.total() << "\n";

    // Сохранение/загрузка
    lib.save_to_file("library.txt");
    std::cout << "\nСохранено в library.txt\n";

    Library lib2;
    lib2.load_from_file("library.txt");
    std::cout << "Загружено в lib2: " << lib2.total() << " книг\n";

    return 0;
}