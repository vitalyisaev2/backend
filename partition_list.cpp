#include <fstream>
#include <sstream>
#include <tuple>

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/sysmacros.h>

#include <./partition_list.h>

PartitionList::PartitionList()
    : partitions(0)
{

    // распарсить список разделов из procfs
    std::ifstream infile("/proc/partitions");
    std::string line;

    // пропустить две первые пустые строки
    for (size_t i = 0; i < 2; i++) {
        std::getline(infile, line);
    }

    // сформировать список разделов
    while (std::getline(infile, line)) {
        std::istringstream ss(line);
        PartitionInfo *pi = new PartitionInfo;
        ss >> pi->major >> pi->minor >> pi->blocks >> pi->name;
        this->partitions.push_back(pi);
    }

}

// get_device возвращает major/minor номера раздела
std::tuple<unsigned int, unsigned int> get_device_id(const char *path)
{
    struct stat buf;

    auto ret = stat(path, &buf);
    if (ret != 0) {
        auto msg = std::string("failed to call stat for path ") + std::string(path);
        throw std::runtime_error(msg);
    }

    return std::make_tuple(major(buf.st_dev), minor(buf.st_dev));
}


std::string PartitionList::GetPartitionByPath(const char *path) const
{
    unsigned int major_id, minor_id;
    std::tie(major_id, minor_id) = get_device_id(path);

    for (auto const &pi: this->partitions) {
        if (pi->major == major_id && pi->minor == minor_id) {
            return pi->name;
        }
    }

    auto msg = std::string("failed to determine partition for path ") + std::string(path);
    throw std::runtime_error(msg);
}

PartitionList::~PartitionList()
{
    for (auto &pi: this->partitions) {
        delete pi;
    }
}
