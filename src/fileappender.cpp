#include "fileappender.h"
#include "logmessage.h"

#include <stdio.h>
#include <iostream>
#include <sstream>
#include <vector>

#ifndef _WIN32
#include <unistd.h>
#endif

using namespace std;

FileAppender::FileAppender(std::string path, std::string filename, int files, long long maxSize) :
    m_path(path), m_filename(filename), m_files(files), m_maxSize(maxSize), m_index(-1) {

    moveToNext();
}



FileAppender::~FileAppender() {
    finish();
}

void FileAppender::finish()
{
    if(m_fp) {
#ifndef _WIN32
        int wfd = fileno(m_fp);
        if(wfd != -1)
        {
            fsync(wfd);
        }
#endif
        fclose(m_fp);
        m_fp = NULL;
    }
}

void FileAppender::output(const Messages &messages)
{
    ostringstream oss;
    for(auto it = std::begin(messages); it != std::end(messages); ++it) {
        oss << (*it)->message() << endl;
        if(oss.tellp() > 10000){ // limit to 10k per write
            save(oss.str());
            oss.str("");
            oss.clear();
        }
    }
    if(oss.tellp() > 0){
        save(oss.str());
    }
}

void FileAppender::save(std::string msg){
    // save output to file
    // FILE* fp = fopen(m_currentPath.c_str(), "a+");
    FILE *fp = m_fp;
    if(!fp){
        cerr << "Cannot open log file " << m_currentPath << endl;
        return;
    }
    fseek(fp, 0, SEEK_END);
    if(ftell(fp) > m_maxSize){
        // current file reaches limit, move to a new file
        finish();

        moveToNext();
        // fp = fopen(m_currentPath.c_str(), "a+");
        fp = m_fp;
        if(!fp){
            cerr << "Cannot open log file " << m_currentPath << endl;
            return;
        }
    }

    fwrite(msg.c_str(), 1, msg.length(), fp);
    // fclose(fp);
    fflush(fp);
#ifndef _WIN32
    int wfd = fileno(m_fp);
    if (wfd != -1)
    {
        fsync(wfd);
    }
#endif
}

void FileAppender::moveToNext(){
    m_index = (m_index + 1) % m_files;

    char name[256];
    sprintf(name, m_filename.c_str(), m_index);
    m_currentPath = m_path + "/" + name;

    // remove eixsting file if any
    remove(m_currentPath.c_str());
    m_fp = fopen(m_currentPath.c_str(), "a+");
}
