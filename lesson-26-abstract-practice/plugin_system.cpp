#include <iostream>
#include <memory>
#include <vector>
#include <string>

// Плагин-система через интерфейс.

class IPlugin {
public:
    virtual ~IPlugin() = default;
    virtual std::string name() const = 0;
    virtual std::string version() const = 0;
    virtual void execute() = 0;
};

class LogPlugin : public IPlugin {
public:
    std::string name() const override { return "Logger"; }
    std::string version() const override { return "1.0"; }
    void execute() override {
        std::cout << "    → логирование событий\n";
    }
};

class BackupPlugin : public IPlugin {
public:
    std::string name() const override { return "Backup"; }
    std::string version() const override { return "2.1"; }
    void execute() override {
        std::cout << "    → создание резервной копии\n";
    }
};

class SecurityPlugin : public IPlugin {
public:
    std::string name() const override { return "Security"; }
    std::string version() const override { return "1.5"; }
    void execute() override {
        std::cout << "    → проверка прав доступа\n";
    }
};

// Основной код — не знает о конкретных плагинах
class PluginManager {
    std::vector<std::unique_ptr<IPlugin>> plugins_;

public:
    void add(std::unique_ptr<IPlugin> p) {
        plugins_.push_back(std::move(p));
    }

    void run_all() {
        std::cout << "Запуск " << plugins_.size() << " плагинов:\n";
        for (auto& p : plugins_) {
            std::cout << "  " << p->name() << " v" << p->version() << "\n";
            p->execute();
        }
    }

    std::size_t count() const { return plugins_.size(); }
};

int main() {
    PluginManager manager;

    manager.add(std::make_unique<LogPlugin>());
    manager.add(std::make_unique<BackupPlugin>());
    manager.add(std::make_unique<SecurityPlugin>());
    manager.add(std::make_unique<LogPlugin>());   // можно повторно

    manager.run_all();

    std::cout << "\nВсего плагинов: " << manager.count() << "\n";
    std::cout << "(основной код не знает о конкретных классах плагинов)\n";

    return 0;
}