#include "logger.h"
#include "logmessage.h"
#include "logappender.h"
#include "logcollector.h"
#include "consoleappender.h"
#include "fileappender.h"

Logger::Logger()
{
    m_collector = std::make_unique<LogCollector>();
    m_isRunning.store(true);
    m_thread = std::make_unique<std::thread>(&Logger::threadloop, this);
}

Logger &Logger::instance()
{
    static Logger log;
    return log;
}

Logger::~Logger()
{
    finish();
}

void Logger::postMessage(const std::shared_ptr<LogMessage> &message)
{
    m_collector->collect(message);
    m_cv.notify_one();
}

void Logger::finish()
{
    if(!m_isRunning.load())
        return;
    m_isRunning.store(false);
    m_cv.notify_all();
    if(m_thread->joinable())
        m_thread->join();
}

LogLevel Logger::level() const
{
    return m_level;
}

void Logger::setLevel(LogLevel level)
{
    m_level = level;
}

void Logger::outputToConsole()
{
    addAppender(std::make_shared<ConsoleAppender>());
}

void Logger::outputToDirectory(std::string directory, std::string pattern, int nFiles, size_t maxSize)
{
    if (pattern.empty())
    {
        pattern = std::string("kdlog_%d.log");
    }
    addAppender(std::make_shared<FileAppender>(directory, pattern, nFiles, maxSize));
}

void Logger::addAppender(const std::shared_ptr<LogAppender> &appender)
{
    if(!appender)
        return;
    m_appenderMutex.lock();
    m_appenders.push_back(appender);
    m_appenderMutex.unlock();
}

void Logger::threadloop()
{
    while (m_isRunning.load() || m_collector->hasMessage()) {
        if(!m_collector->hasMessage()) {
            std::unique_lock<std::mutex> lock(m_mutex);
            m_cv.wait(lock);
            if(!m_collector->hasMessage())
                break;
        }

        auto &&message = m_collector->messages();
        m_appenderMutex.lock();
        for(auto &appender : m_appenders)
        {
            appender->output(message);
        }
        m_appenderMutex.unlock();
    }
}



