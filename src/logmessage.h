#ifndef LOGMESSAGE_H
#define LOGMESSAGE_H

#include <string>

enum class LogLevel {
    VERBOSE = 0,
    DEBUG,
    INFO,
    WARNING,
    ERROR,
};

class LogMessage
{
public:
    LogMessage(const std::string &module, LogLevel level, const std::string &message);

    const std::string &message() const;

    const LogLevel &level() const;

    const std::string &module() const;

private:
    std::string m_message;
    LogLevel m_level;
    std::string m_module;
};

#endif // LOGMESSAGE_H
