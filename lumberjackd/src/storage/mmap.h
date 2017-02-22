#include "interface.h"

#ifndef MMAP_H_
#define MMAP_H_
    class MmapManager: public StorageManager
    {
        public:
            MmmapManager(std::string data_path);
            ~MmapManager();
            int commit();
            int load();
        private:
            int data_path_fd;
            void *buffer[];
    }
#endif
