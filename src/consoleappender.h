#ifndef CONSOLEAPPENDER_H
#define CONSOLEAPPENDER_H

#include "logappender.h"

class ConsoleAppender : public LogAppender
{
public:
    ConsoleAppender();
    virtual void output(const Messages &messages) override;
};

#endif // CONSOLEAPPENDER_H
