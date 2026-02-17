#include <iostream>
#include <fstream>
#include <string>

class LogCommand {
public:
    virtual ~LogCommand() = default;
    virtual void print(const std::string& message) = 0;
};

class ConsoleLog : public LogCommand {
public:
    void print(const std::string& message) override {
        std::cout << message << std::endl;
    }
};

class FileLog : public LogCommand {
    std::ofstream file;
public:
    FileLog(const std::string& path)
        : file(path, std::ios::app) {
        //  ios::app for adding to the end
    }

    void print(const std::string& message) override {
        if (file.is_open()) {
            file << message << std::endl;
        }
    }
};

void print(LogCommand& cmd) {
    cmd.print("Log message");
}

int main() {
    ConsoleLog consoleLogger;
    print(consoleLogger);

    FileLog fileLogger("application.log");
    print(fileLogger);

    return 0;
}