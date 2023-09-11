#ifndef LOGCOLLECTOR_H
#define LOGCOLLECTOR_H

#include <mutex>
#include <vector>
#include <memory>

class LogMessage;

using Messages = std::vector<std::shared_ptr<LogMessage> >;

class LogCollector
{
public:
    LogCollector();

    bool hasMessage() const;

    void collect(const std::shared_ptr<LogMessage> &message);
    Messages messages();

private:
    mutable std::mutex m_mutex;
    Messages m_messages;
};

#endif // LOGCOLLECTOR_H
