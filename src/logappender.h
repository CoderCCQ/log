#ifndef LOGAPPENDER_H
#define LOGAPPENDER_H

#include "logcollector.h"

class LogAppender
{
public:
    LogAppender();
    virtual void output(const Messages &messages) = 0;
};

#endif // LOGAPPENDER_H
