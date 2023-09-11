#ifndef LOGGER_H
#define LOGGER_H

#include <memory>
#include <vector>
#include <thread>
#include <atomic>
#include <condition_variable>

#include "logmessage.h"

class LogCollector;
class LogAppender;
class LogMessageQueue;

class Logger
{
public:

    enum class Appender {
        CONSOLE = 0,
        FILE,
        NETWORK
    };

    static Logger &instance();
    ~Logger();

    void postMessage(const std::shared_ptr<LogMessage> &message);

    LogLevel level() const;
    void setLevel(LogLevel level);

    void addAppender(const std::shared_ptr<LogAppender> &appender);

    void finish();
    void outputToConsole();
    void outputToDirectory(std::string directory, std::string pattern, int nFiles, size_t maxSize);

private:
    Logger();
    void threadloop();

private:
    LogLevel m_level = LogLevel::INFO;

    std::unique_ptr<LogCollector> m_collector;
    std::vector<std::shared_ptr<LogAppender> > m_appenders;
    std::mutex m_appenderMutex;

    std::unique_ptr<std::thread> m_thread;
    std::mutex m_mutex;
    std::condition_variable m_cv;
    std::atomic_bool m_isRunning;
};

#endif // LOGGER_H
