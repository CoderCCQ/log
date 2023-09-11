#include "logmessage.h"

LogMessage::LogMessage(const std::string &module, LogLevel level, const std::string &message)
    : m_message(message)
    , m_level(level)
    , m_module(module)
{

}

const std::string &LogMessage::message() const
{
    return m_message;
}

const LogLevel &LogMessage::level() const
{
    return m_level;
}

const std::string &LogMessage::module() const
{
    return m_module;
}
