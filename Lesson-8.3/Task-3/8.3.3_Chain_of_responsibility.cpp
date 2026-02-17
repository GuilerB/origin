#include <iostream>
#include <fstream>
#include <memory>
#include <stdexcept>
#include <string>

class LogMessage {
public:
    enum class Type { WARNING, ERROR, FATAL_ERROR, UNKNOWN };

    Type type() const { return type_; }
    const std::string& message() const { return message_; }

    LogMessage(Type type, std::string msg) : type_(type), message_(std::move(msg)) {}

private:
    Type type_;
    std::string message_;
};

class Handler {
public:
    virtual ~Handler() = default;

    // set next handler in chain and return the next object pointer
    Handler* setNext(std::unique_ptr<Handler> next) {
        Handler* nextHandler = next.get();
        next_ = std::move(next);
        return nextHandler; // return the next object, not current
    }

    // base handler method
    void handle(const LogMessage& msg) const {
        if (canHandle(msg)) {
            process(msg);
        }
        else if (next_) {
            next_->handle(msg);
        }
        else {
            throw std::logic_error("No handler can process the message and chain is incomplete");
        }
    }

protected:
    virtual bool canHandle(const LogMessage& msg) const = 0;

    virtual void process(const LogMessage& msg) const = 0;

private:
    std::unique_ptr<Handler> next_;
};

class FatalErrorHandler : public Handler {
protected:
    bool canHandle(const LogMessage& msg) const override {
        return msg.type() == LogMessage::Type::FATAL_ERROR;
    }

    void process(const LogMessage& msg) const override {
        throw std::runtime_error("FATAL ERROR: " + msg.message());
    }
};

class ErrorHandler : public Handler {
public:
    explicit ErrorHandler(std::string filePath) : filePath_(std::move(filePath)) {}

protected:
    bool canHandle(const LogMessage& msg) const override {
        return msg.type() == LogMessage::Type::ERROR;
    }

    void process(const LogMessage& msg) const override {
        std::ofstream file(filePath_, std::ios::app);
        if (file.is_open()) {
            file << "[ERROR] " << msg.message() << std::endl;
            std::cout << "[INFO] Error logged to file: " << filePath_ << std::endl;
        }
        else {
            std::cerr << "[ERROR] Failed to open error log file: " << filePath_ << std::endl;
        }
    }

private:
    std::string filePath_;
};

class WarningHandler : public Handler {
protected:
    bool canHandle(const LogMessage& msg) const override {
        return msg.type() == LogMessage::Type::WARNING;
    }

    void process(const LogMessage& msg) const override {
        std::cout << "[WARNING] " << msg.message() << std::endl;
    }
};

class UnknownMessageHandler : public Handler {
protected:
    bool canHandle(const LogMessage& msg) const override {
        return true;
    }

    void process(const LogMessage& msg) const override {
        throw std::runtime_error("Unhandled message type: " + msg.message());
    }
};

// universal log chain function
std::unique_ptr<Handler> createLoggingChain(const std::string& errorFilePath) {
    auto fatalHandler = std::make_unique<FatalErrorHandler>();

    // fluent interface - due to returning "this" in the Handler::setNext method
    fatalHandler->setNext(std::make_unique<ErrorHandler>(errorFilePath))
        ->setNext(std::make_unique<WarningHandler>())
        ->setNext(std::make_unique<UnknownMessageHandler>());

    return fatalHandler;
}

int main() {
    std::cout << "\n\n\n" << std::endl;

    auto logger = createLoggingChain("application_errors.log");

    try {
        //std::cout << "Warning:" << std::endl;
        logger->handle(LogMessage(
            LogMessage::Type::WARNING,
            "I warn you, Neo..."
        ));
        std::cout << "\n" << std::endl;

        //std::cout << "Ordinary error:" << std::endl;
        logger->handle(LogMessage(
            LogMessage::Type::ERROR,
            "I'm getting a connection error, Neo..."
        ));
        std::cout << "I logged it to application_errors.log" << std::endl;
        std::cout << "\n" << std::endl;

        try {
            logger->handle(LogMessage(LogMessage::Type::FATAL_ERROR, "Fatal error, Neo!"));
        }
        catch (const std::exception& e) {
            std::cerr << "A fatal error is observed: " << e.what() << std::endl;
        }

        try {
            logger->handle(LogMessage(static_cast<LogMessage::Type>(99), "Unknown error"));
        }
        catch (const std::exception& e) {
            std::cerr << "An unknown error observed: " << e.what() << std::endl;
        }

    }
    catch (const std::exception& e) {
        std::cerr << "Unhandled exception: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

