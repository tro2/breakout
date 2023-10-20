#pragma once

#include <string>

enum LogLevel
{
    DEBUG,
    WARN,
    ERROR
};

class Logger
{
public:
    static void log(LogLevel level, const std::string& message);

private:
    static const std::string currentDateTime();
};
