#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <chrono>
#include <string>

// Одна задача — три контейнера.

using Clock = std::chrono::high_resolution_clock;
using ms = std::chrono::milliseconds;

template <typename Container>
long long time_push_back(int n) {
    Container c;
    auto start = Clock::now();
    for (int i = 0; i < n; ++i) c.push_back(i);
    auto end = Clock::now();
    return std::chrono::duration_cast<ms>(end - start).count();
}

template <typename Container>
long long time_push_front(int n) {
    Container c;
    auto start = Clock::now();
    for (int i = 0; i < n; ++i) c.push_front(i);
    auto end = Clock::now();
    return std::chrono::duration_cast<ms>(end - start).count();
}

int main() {
    const int N = 100'000;

    std::cout << "=== push_back " << N << " элементов ===\n";
    std::cout << "vector: " << time_push_back<std::vector<int>>(N) << " ms\n";
    std::cout << "deque:  " << time_push_back<std::deque<int>>(N) << " ms\n";
    std::cout << "list:   " << time_push_back<std::list<int>>(N) << " ms\n\n";

    std::cout << "=== push_front " << N << " элементов ===\n";
    // vector не имеет push_front — пропускаем
    std::cout << "deque:  " << time_push_front<std::deque<int>>(N) << " ms\n";
    std::cout << "list:   " << time_push_front<std::list<int>>(N) << " ms\n\n";

    std::cout << "=== Обход (сумма) ===\n";

    std::vector<int> v(N, 1);
    std::deque<int> d(N, 1);
    std::list<int> l(N, 1);

    auto start = Clock::now();
    long long sv = 0;
    for (int x : v) sv += x;
    auto end = Clock::now();
    std::cout << "vector: " << std::chrono::duration_cast<ms>(end - start).count()
              << " ms (сумма " << sv << ")\n";

    start = Clock::now();
    long long sd = 0;
    for (int x : d) sd += x;
    end = Clock::now();
    std::cout << "deque:  " << std::chrono::duration_cast<ms>(end - start).count()
              << " ms (сумма " << sd << ")\n";

    start = Clock::now();
    long long sl = 0;
    for (int x : l) sl += x;
    end = Clock::now();
    std::cout << "list:   " << std::chrono::duration_cast<ms>(end - start).count()
              << " ms (сумма " << sl << ")\n";

    return 0;
}
