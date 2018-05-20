#include <iostream>
#include <./partition_list.h>
#include "disk_usage_watcher.h"

int main(int argc, char **argv) {

    if (argc != 2) {
        std::cerr << "wrong amount of arguments" << std::endl;
        return 1;
    }

    try {
        PartitionList pl;
        auto partition = pl.GetPartitionByPath(argv[1]);
        auto watcher = DiskUsageWatcher(partition, std::chrono::seconds(1));
        watcher.Run();
    } catch (std::exception const& ex) {
        std::cerr << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
