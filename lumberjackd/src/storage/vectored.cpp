#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "vectored.h"

using namespace std;

VectoredIOManager::VectoredIOManager(std::string data_path, int max_buffers)
{
    this->data_path_fd = open(data_path.c_str(), O_RDWR|O_CREAT);
    if(this->data_path_fd == -1){
        // TODO handle error
    }
    struct iovec iobufs[max_buffers];
    this->iov = (struct iovec[])(iobufs);
    void b[max_buffers][MAX_BUFFER_SIZE];
    this->bufs = (void[][])(b);
    for(int i = 0; i < max_buffers; i++){
        this->iov[i].iov_base = (void*)(this->bufs[i]);
        this->iov[i].iov_len = sizeof(this->bufs[i]);
    }
}

VectoredIOManager::select_buffer(void *addr)
{
    for(int i = 0; i < sizeof(this->iov); i++){
        if(this->iov[i].iov_len < MAX_BUFFER_SIZE){
            this->bufs[i] = addr;
            this->iov[i].iov_base = addr;
            this->iov[i].iov_len = sizeof(addr);
            return 0;
        }
    }
    // TODO handle error
    return -1;
}

VectoredIOManager::commit()
{
    return writev(this->data_path_fd, this->iov, sizeof(this->iov));
}

VectoredIOManager::load()
{
    return readv(this->data_path_fd, this->iov, sizeof(this->iov));
}
