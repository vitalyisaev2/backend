#ifndef PARTITION_LIST_HPP
#define PARTITION_LIST_HPP

#include <iostream>
#include <vector>

class IPartitionList {
    public:
        virtual ~IPartitionList() {};
        virtual std::string GetPartitionByPath(const char* path) = 0;
};

struct PartitionInfo {
    unsigned int major;
    unsigned int minor;
    unsigned long blocks;
    std::string name;
};

class PartitionList : IPartitionList {
    public:
        PartitionList();
        ~PartitionList();
        virtual std::string GetPartitionByPath(const char* path);
    private:
        std::vector<PartitionInfo*> partitions;
};


#endif
