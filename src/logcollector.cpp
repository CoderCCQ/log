#include "logcollector.h"

LogCollector::LogCollector()
{

}

bool LogCollector::hasMessage() const
{
    std::lock_guard<std::mutex> lock(m_mutex);
    return !m_messages.empty();
}

void LogCollector::collect(const std::shared_ptr<LogMessage> &message)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_messages.emplace_back(message);
}

Messages LogCollector::messages()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    Messages messages;
    messages.swap(m_messages);
    return messages;
}

