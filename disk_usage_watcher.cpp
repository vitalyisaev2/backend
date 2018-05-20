#include "disk_usage_watcher.h"

#include <vector>
#include <thread>
#include <iostream>

DiskUsageWatcher::DiskUsageWatcher(
    const std::string &device,
    std::chrono::seconds periodicity)
    :
    statFileReader(new StatFileReader(device)),
    periodicity(periodicity)
{
}

DiskUsageWatcher::~DiskUsageWatcher()
{
    delete (this->statFileReader);
}

void DiskUsageWatcher::Run()
{
    while (true) {
        std::this_thread::sleep_for(this->periodicity);
        auto measurement = this->statFileReader->Measure();
        std::cout << measurement << std::endl;
    }
}
