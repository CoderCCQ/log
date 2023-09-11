#ifndef FILEAPPENDER_H
#define FILEAPPENDER_H


#include "logappender.h"

class FileAppender : public LogAppender
{
public:
    FileAppender(std::string path, std::string filename, int files, long long maxSize);
    ~FileAppender();
    virtual void output(const Messages &messages) override;
    void finish();

private:
    FILE *m_fp;
    std::string m_path;
    std::string m_filename;
    std::string m_currentPath;
    int m_files;
    long long m_maxSize;
    int m_index;

    void moveToNext();
    void save(std::string msg);
};

#endif // FILEAPPENDER_H
