//
// Created by vitaly on 5/20/18.
//

#ifndef BACKEND_STAT_FILE_READER_H
#define BACKEND_STAT_FILE_READER_H


#include <string>
#include <fstream>

// IStatFileReader provides a method for measuring io_ticks of the block device -
// the useful metric to estimate device utilization
class IStatFileReader
{
public:
    virtual ~IStatFileReader() {};
    virtual unsigned long Measure() = 0;
};

class StatFileReader: public IStatFileReader
{
public:
    StatFileReader(const std::string &);
    ~StatFileReader();
    unsigned long Measure();
private:
    std::string path;
    std::string buf;
    std::ifstream fd;
};


#endif //BACKEND_STAT_FILE_READER_H
