#include "consoleappender.h"
#include <iostream>
#include "logmessage.h"

#ifndef _WIN32
#define COLOR_END "\e[0m"
#define BLACK "\e[0;30m"
#define L_BLACK "\e[1;30m"
#define RED "\e[0;31m"
#define L_RED "\e[1;31m"
#define GREEN "\e[0;32m"
#define L_GREEN "\e[1;32m"
#define BROWN "\e[0;33m"
#define YELLOW "\e[1;33m"
#define BLUE "\e[0;34m"
#define L_BLUE "\e[1;34m"
#define PURPLE "\e[0;35m"
#define L_PURPLE "\e[1;35m"
#define CYAN "\e[0;36m"
#define L_CYAN "\e[1;36m"
#define GRAY "\e[0;37m"
#define WHITE "\e[1;37m"

#define BOLD "\e[1m"
#define UNDERLINE "\e[4m"
#define BLINK "\e[5m"
#define REVERSE "\e[7m"
#define HIDE "\e[8m"
#define CLEAR "\e[2J"
#define CLRLINE "\r\e[K"

static std::string getColor(LogLevel level) {
    switch (level) {
    case LogLevel::VERBOSE:
        return std::string(WHITE);
    case LogLevel::DEBUG:
        return std::string(GRAY);
    case LogLevel::INFO:
        return std::string(GREEN);
    case LogLevel::WARNING:
        return std::string(YELLOW);
    case LogLevel::ERROR:
        return std::string(RED);
    default:
        return std::string(WHITE);
    }
}

#else

static const LogLevel LOG_ERROR = LogLevel::ERROR;
#include <Windows.h>
#include <map>

static void setColor(const LogLevel &level)
{
    int color = 0x7;

    switch (level) {
    case LogLevel::VERBOSE:
        color = 0x7;
        break;
    case LogLevel::DEBUG:
        color = 0x8;
        break;
    case LogLevel::INFO:
        color = 0x2;
        break;
    case LogLevel::WARNING:
        color = 0x6;
        break;
    case LOG_ERROR:
        color = 0x4;
        break;
    default:
        color = 0x7;
        break;
    }

    HANDLE hdl = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hdl, color | FOREGROUND_INTENSITY);
}

//e[0;37m2022e[0m
static void consoleWin32(const std::shared_ptr<LogMessage> &message) {
    setColor(message->level());
    std::cout << message->message() << std::endl;
}
#endif

ConsoleAppender::ConsoleAppender()
{

}

void ConsoleAppender::output(const Messages &messages)
{
#ifdef _WIN32
    for(auto it = std::begin(messages); it != std::end(messages); ++it) {
        consoleWin32(*it);
    }
#else
    std::string output;
    for(auto it = std::begin(messages); it != std::end(messages); ++it) {
        output.append(getColor((*it)->level()));
        output.append((*it)->message());
        output.append(std::string(COLOR_END));
        output.append("\n");
    }
    std::cout << output;
#endif
}
