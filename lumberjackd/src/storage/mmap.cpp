#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "mmap.h"

using namespace std;

MmapManager::MmapManager(std::string data_path)
{
    this->data_path_fd = open(data_path.c_str(), O_RDWR|O_CREAT);    
    void *buf[];
    this->buffer = buf;
}

