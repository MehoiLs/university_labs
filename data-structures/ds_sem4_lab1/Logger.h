#ifndef DS_SEM3_LAB1_LOGGER_H
#define DS_SEM3_LAB1_LOGGER_H

#include <iostream>
#include <ctime>
#include <typeinfo>
#include <chrono>
#include <ctime>

using std::cin;
using std::cout;

extern bool isLoggingEnabled;

template<typename Clazz>
class Logger {
private:

    [[nodiscard]] std::string getCurrentTime() const {
        const auto now = std::chrono::system_clock::now();
        const auto now_c = std::chrono::system_clock::to_time_t(now);
        char buf[100];
        std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now_c));
        return buf;
    }
public:
    explicit Logger() = default;

    void log(const std::string& message) const {
        if (isLoggingEnabled) {
            std::cout << getCurrentTime() << " " << typeid(Clazz).name() << ": " << message << std::endl;
        }
    }

    void error(const std::string& message) const {
        if (isLoggingEnabled) {
            std::cerr << getCurrentTime() << " " << typeid(Clazz).name() << ": " << message << std::endl;
        }
    }
};

#endif //DS_SEM3_LAB1_LOGGER_H
