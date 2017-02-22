#ifndef STORAGE_INTERFACE_H_
#define STORAGE_INTERFACE_H_
    class StorageManager
    {
        public:
            virtual ~StorageManager() {}
            virtual int commit() const = 0;
    };
#endif
