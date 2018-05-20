#ifndef BACKEND_PARTITION_LIST_H
#define BACKEND_PARTITION_LIST_H

#include <iostream>
#include <vector>

class IPartitionList
{
public:
    virtual ~IPartitionList()
    {};
    virtual std::string GetPartitionByPath(const char *path) const = 0;
};

struct PartitionInfo
{
    unsigned int major;
    unsigned int minor;
    unsigned long blocks;
    std::string name;
};

class PartitionList: IPartitionList
{
public:
    PartitionList();
    ~PartitionList();
    virtual std::string GetPartitionByPath(const char *path) const;
private:
    std::vector<PartitionInfo *> partitions;
};

#endif
