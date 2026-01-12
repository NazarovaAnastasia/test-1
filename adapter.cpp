#include <iostream>
#include <string>

class ExternalLogger {
public:
    void LogMessage(const std::string& msg) {
        std::cout << "External log: " << msg << std::endl;
    }
};

class Logger {
public:
    virtual ~Logger() = default;
    virtual void Log(const std::string& message) = 0;
};

// Адаптер
class LoggerAdapter : public Logger {
private:
    ExternalLogger externalLogger;
    
public:
    void Log(const std::string& message) override {
        externalLogger.LogMessage(message);
    }
};

class AdvancedExternalLogger {
public:
    void writeLog(const std::string& text, int level) {
        std::cout << "Advanced log [Level " << level << "]: " << text << std::endl;
    }
};

class AdvancedLoggerAdapter : public Logger {
private:
    std::unique_ptr<AdvancedExternalLogger> advancedLogger;
    
public:
    AdvancedLoggerAdapter() : advancedLogger(std::make_unique<AdvancedExternalLogger>()) {}
    
    void Log(const std::string& message) override {
        advancedLogger->writeLog(message, 1);
    }
};

int main() {
    LoggerAdapter simpleAdapter;
    AdvancedLoggerAdapter advancedAdapter;
    
    simpleAdapter.Log("This is a simple message");
    advancedAdapter.Log("This is an advanced message");
    
    return 0;
}
