#include <string>
#include <capnp/message.h>
#include <capnp/serialize-packed.h>
#include "net.capnp.h"
#include "disk.h"

#ifndef _NET_H
#define _NET_H

using namespace std;
using namespace disk;

namespace net {
    class Net {
        public:
            virtual void serve();
        private:
            std::string host;
            unsigned int port;
            bool should_run;
    }

    class TCPNet: public Net {
        public:
            TCPNet(std::string host, unsigned int port);
            ~TCPNet();
            void serve();
            void publish();

        private:
            void _unblock(int fd);
            std::vector<TCPConn> subscribers;
            std::vector<TCPConn> open_connections;
            disk::Writer *writer;
            std::vector<*disk::Reader> readers;
    }

    class TCPConn {
        public:
            TCPConn(int fd);
            ~TCPConn();
            void read(void*[] dest);
            void write(void*[] payload);
        private:
            int fd;
            bool is_subscribed;
    }

    class UDPNet: public Net {
        public:
            UDPNet(std::string host, unsigned int port);
            ~UDPNet();
            void serve();
        private:
            disk::Writer *writer;
    }
}
#endif
