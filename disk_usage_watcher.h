#ifndef BACKEND_DISK_USAGE_WATCHER_H
#define BACKEND_DISK_USAGE_WATCHER_H

#include <chrono>
#include <string>
#include <fstream>
#include "stat_file_reader.h"

// IDiskUsageWatcher is an interface for watching disk/partition utilization
class IDiskUsageWatcher
{
public:
    virtual ~IDiskUsageWatcher() {};
    virtual void Run() = 0;
};

// DiskUsageWatcher observes disk or partition utilization
class DiskUsageWatcher: public IDiskUsageWatcher
{
public:
    DiskUsageWatcher(const std::string &device, std::chrono::seconds periodicity);
    ~DiskUsageWatcher();
    // Run launches disk utilization watching (blocking call)
    void Run();
private:
    // statFileReader - provides actual ioticks for device;
    IStatFileReader *statFileReader;
    // periodicity - time gap between measurements
    std::chrono::seconds periodicity;
    // previous - previous measured value
    unsigned long previous;

};

#endif //BACKEND_DISK_USAGE_WATCHER_H
