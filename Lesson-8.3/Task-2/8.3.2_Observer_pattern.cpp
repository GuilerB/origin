#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <functional>
#include <algorithm>

class Observer {
public:
    virtual void onWarning(const std::string& message) {}
    virtual void onError(const std::string& message) {}
    virtual void onFatalError(const std::string& message) {}
    virtual ~Observer() = default;
};

class Logger {
public:
    void addObserver(std::shared_ptr<Observer> observer) {
        observers_.push_back(observer);
    }

    void warning(const std::string& message) const {
        notifyObservers([message](Observer& obs) { obs.onWarning(message); });
    }

    void error(const std::string& message) const {
        notifyObservers([message](Observer& obs) { obs.onError(message); });
    }

    void fatalError(const std::string& message) const {
        notifyObservers([message](Observer& obs) { obs.onFatalError(message); });
    }

private:
    mutable std::vector<std::weak_ptr<Observer>> observers_;

    void notifyObservers(std::function<void(Observer&)> action) const {
        // Clear the list of null observers and notify no-null observers 
        for (auto it = observers_.begin(); it != observers_.end(); ) {
            if (auto observer = it->lock()) {
                action(*observer);
                ++it;
            }
            else {
                it = observers_.erase(it);
            }
        }
    }
};

class ConsoleWarning : public Observer {
public:
    void onWarning(const std::string& message) override {
        std::cout << "[WARNING] " << message << std::endl;
    }
};

class FileError : public Observer {
    std::string filePath_;
public:
    FileError(const std::string& filePath) : filePath_(filePath) {}

    void onError(const std::string& message) override {
        std::ofstream file(filePath_, std::ios::app);
        if (file.is_open()) {
            file << "[ERROR] " << message << std::endl;
        }
    }
};

class ConsoleAndFileFatalError : public Observer {
    std::string filePath_;
public:
    ConsoleAndFileFatalError(const std::string& filePath)
        : filePath_(filePath) {
    }

    void onFatalError(const std::string& message) override {
        std::cout << "[FATAL] " << message << std::endl;

        std::ofstream file(filePath_, std::ios::app);
        if (file.is_open()) {
            file << "[FATAL] " << message << std::endl;
        }
    }
};

int main() {
    Logger logger;

    // create observers
    auto consoleWarning = std::make_shared<ConsoleWarning>();
    auto fileError = std::make_shared<FileError>("errors.log");
    auto fatalObserver = std::make_shared<ConsoleAndFileFatalError>("fatal.log");

    // register the observers inside the logger
    logger.addObserver(consoleWarning);
    logger.addObserver(fileError);
    logger.addObserver(fatalObserver);

    // generate events
    logger.warning("Warning");
    logger.error("Connection to database failed");
    logger.fatalError("Core critical error");

    return 0;
}