//
// Created by vitaly on 5/20/18.
//

#include <vector>
#include <sstream>
#include <iostream>
#include "stat_file_reader.h"

// buildStatFilePath creates a path to file containing device stats on Linux machine
// TODO: sysfs may be mounted to a different directory...
std::string buildStatFilePath(const std::string& device)
{
    return std::string("/sys/block/") + device + std::string("/stat");
}

StatFileReader::StatFileReader(const std::string &device)
    :
    path(buildStatFilePath(device)), fd(path)
{}

StatFileReader::~StatFileReader()
{
    this->fd.close();
}

unsigned long StatFileReader::Measure()
{
    // read whole file to a string
    this->fd.clear();
    this->fd.seekg(0, this->fd.beg);
    getline(this->fd, this->buf);

    // take 10th item from string (io_ticks);
    // see https://www.kernel.org/doc/Documentation/block/stat.txt for format description

    std::istringstream ss(this->buf);
    unsigned long result;
    for (auto i = 0; i < 10; i++) {
        ss >> result;
    }

    return result;
}
