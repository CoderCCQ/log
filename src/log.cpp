/*
 * Copyright (C) 2020 Kandao Technology Co.,Ltd.
 *
 * This software is the property of Kandao Technology Co.,Ltd.
 * Use or redistribution of this software without written permission
 * from Kandao Technology Co.,Ltd is prohibited.
 *
 * @project  Kandao OS
 * @version  1.0
 * @author   Xing Dongfeng
 * @created  Fri Jul 28 2020
 */
#include "log.h"
#include "logger.h"
#include <stdio.h>
#include <stdarg.h>
#include <string>
#include <memory>
#include <iostream>
#include <sstream>
#include <ctime>
#include <cstring>
#include <iomanip>
#include <chrono>

#include "logger.h"

namespace
{
#define MSG_LEN 1024

  static const char *LogLevelNames[] = {"V", "D", "I", "W", "E"};

  /**
   * Current time up to miliseconds.
   */
  std::string currentTime()
  {
    using std::chrono::system_clock;
    auto currentTime = std::chrono::system_clock::now();
    char buffer[32];
    auto transformed = currentTime.time_since_epoch().count() / 1000000;
    auto millis = transformed % 1000;

    std::time_t tt;
    tt = system_clock::to_time_t(currentTime);
    auto timeinfo = localtime(&tt);
    strftime(buffer, sizeof(buffer), "%FT%T", timeinfo);
    sprintf(buffer + strlen(buffer), ".%03d", (int)millis);
    return std::string(buffer);
  }

  void _log(eLogLevel level, const char *module, const char *fmt, va_list args)
  {
    if(level < (eLogLevel)Logger::instance().level())
      return;
    // convert fmt and args to string
    char data[MSG_LEN];
    va_list bakargs;
    va_copy(bakargs, args);
    int len = vsnprintf(data, MSG_LEN, fmt, args);

    std::string text;
    if (len < MSG_LEN)
    {
        text = std::string(data);
    }
    else
    {
        char *dataExt = new char[len + 1];
        len = vsnprintf(dataExt, len+1, fmt, bakargs);
        text = std::string(dataExt);
        delete[] dataExt;
        va_end(bakargs);
    }

    // forward the message to Logger
    std::string message = currentTime() + "[" + std::string(module) + "]" + "[" + std::string(LogLevelNames[level]) + "]" + text;
    std::shared_ptr<LogMessage> msg = std::make_shared<LogMessage>(module, (LogLevel)level, message);
    Logger::instance().postMessage(msg);
  }
}

void logV(const char *module, const char *fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  _log(LOG_VERBOSE, module, fmt, args);
  va_end(args);
}

void logD(const char *module, const char *fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  _log(LOG_DEBUG, module, fmt, args);
  va_end(args);
}

void logI(const char *module, const char *fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  _log(LOG_INFO, module, fmt, args);
  va_end(args);
}

void logW(const char *module, const char *fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  _log(LOG_WARNING, module, fmt, args);
  va_end(args);
}

void logE(const char *module, const char *fmt, ...)
{
  va_list args;
  va_start(args, fmt);
  _log(LOG_ERROR, module, fmt, args);
  va_end(args);
}

void kdlog_output_to_console()
{
  Logger::instance().outputToConsole();
}

void kdlog_output_to_file(const char *directory, const char *pattern, int nFiles, unsigned int maxSize)
{
  Logger::instance().outputToDirectory(directory, pattern, nFiles, maxSize);
}

void kdlog_finish()
{
  Logger::instance().finish();
}

void kdlog_set_level(eLogLevel level)
{
  Logger::instance().setLevel((LogLevel)level);
}

//void kdlog_enable_all_modules()
//{
//  Logger::instance().enableAllModules();
//}

//void kdlog_disable_all_modules()
//{
//  Logger::instance().disableAllModules();
//}

//void kdlog_enable_module(const char *module)
//{
//  Logger::instance().enableModule(module);
//}

//void kdlog_disable_module(const char *module)
//{
//  Logger::instance().disableModule(module);
//}
