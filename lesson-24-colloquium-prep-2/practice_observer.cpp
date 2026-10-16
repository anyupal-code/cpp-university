#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <algorithm>

// Задача 4. Упрощённый наблюдатель (observer).

class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void on_update(int value) = 0;
    virtual std::string name() const = 0;
};

class Publisher {
private:
    int value_ = 0;
    std::vector<std::weak_ptr<IObserver>> observers_;

public:
    void subscribe(const std::shared_ptr<IObserver>& obs) {
        observers_.push_back(obs);
    }

    void set_value(int v) {
        value_ = v;
        notify();
    }

    int value() const { return value_; }

private:
    void notify() {
        // Чистим мёртвые weak_ptr
        observers_.erase(
            std::remove_if(observers_.begin(), observers_.end(),
                           [](const auto& w) { return w.expired(); }),
            observers_.end()
        );

        for (auto& w : observers_) {
            if (auto obs = w.lock()) {
                obs->on_update(value_);
            }
        }
    }
};

class ConsoleObserver : public IObserver {
    std::string name_;
public:
    explicit ConsoleObserver(std::string name) : name_(std::move(name)) {}

    void on_update(int value) override {
        std::cout << "  [" << name_ << "] получил значение: " << value << "\n";
    }

    std::string name() const override { return name_; }
};

class CounterObserver : public IObserver {
    std::string name_;
    int updates_ = 0;
public:
    explicit CounterObserver(std::string name) : name_(std::move(name)) {}

    void on_update(int) override {
        ++updates_;
        std::cout << "  [" << name_ << "] обновлений: " << updates_ << "\n";
    }

    std::string name() const override { return name_; }
};

int main() {
    Publisher pub;

    {
        auto o1 = std::make_shared<ConsoleObserver>("Console1");
        auto o2 = std::make_shared<CounterObserver>("Counter1");

        pub.subscribe(o1);
        pub.subscribe(o2);

        std::cout << "=== set_value(10) ===\n";
        pub.set_value(10);

        std::cout << "\n=== set_value(20) ===\n";
        pub.set_value(20);

        std::cout << "\n=== o1 выходит из области видимости ===\n";
    }   // o1, o2 уничтожатся здесь

    std::cout << "\n=== set_value(30) — подписчики мертвы ===\n";
    pub.set_value(30);

    std::cout << "\n(weak_ptr не продлил жизнь наблюдателей)\n";

    return 0;
}