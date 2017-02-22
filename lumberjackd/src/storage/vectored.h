#include <sys/uio.h>
#include "interface.h"

#ifndef MAX_BUFFER_SIZE
#define MAX_BUFFER_SIZE 4096
#endif


#ifndef VECTORED_H_
#define VECTORED_H_
    class VectoredIOManager: public StorageManager
    {
        public:
            VectoredIOManager(std::string data_path, int max_buffers);
            ~VectoredIOManager();
            int select_buffer(void *addr);
            int commit();
            int load();
        private:
            int data_path_fd;
            struct iovec iov[];
            void bufs[][];
    }
#endif
