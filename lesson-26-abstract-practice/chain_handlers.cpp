#include <iostream>
#include <memory>
#include <string>

// Chain of Responsibility: цепочка обработчиков.

class Handler {
protected:
    std::shared_ptr<Handler> next_;

public:
    virtual ~Handler() = default;

    void set_next(std::shared_ptr<Handler> next) {
        next_ = std::move(next);
    }

    virtual bool handle(int request) = 0;
};

class RangeHandler : public Handler {
    int min_, max_;
    std::string label_;
public:
    RangeHandler(int min, int max, std::string label)
        : min_(min), max_(max), label_(std::move(label)) {}

    bool handle(int request) override {
        if (request >= min_ && request <= max_) {
            std::cout << "  " << label_ << " обработал " << request << "\n";
            return true;
        }
        if (next_) return next_->handle(request);

        std::cout << "  " << request << " не обработан (конец цепочки)\n";
        return false;
    }
};

int main() {
    // Строим цепочку: small → medium → large
    auto small = std::make_shared<RangeHandler>(1, 10, "Small");
    auto medium = std::make_shared<RangeHandler>(11, 100, "Medium");
    auto large = std::make_shared<RangeHandler>(101, 1000, "Large");

    small->set_next(medium);
    medium->set_next(large);

    std::cout << "=== Запросы ===\n";
    for (int req : {5, 50, 500, 5000}) {
        std::cout << "Запрос " << req << ":\n";
        small->handle(req);
    }

    return 0;
}