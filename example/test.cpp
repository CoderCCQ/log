#include <iostream>

#include "log.h"
using namespace std;

static const char * module = "ccq";

int main()
{
    cout << "Hello World!" << endl;
    kdlog_set_level(LOG_VERBOSE);
    kdlog_output_to_console();
    kdlog_output_to_file(".", "hhh_%d.log", 3, 1024*1024);
    LOGV("123");
    LOGD("123");
    LOGI("123");
    LOGW("123");
    LOGE("123");

//    kdlog_finish();
    return 0;
}
