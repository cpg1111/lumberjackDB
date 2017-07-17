#include "net.h"
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <fcntl.h>

#define _NO_SOCK_EXCEPTION "unable to open a socket";
#define _UNABLE_TO_SHARE_ADDR_EXCEPTION "master socket unable to share address";
#define _UNABLE_TO_BIND_ADDR_EXCEPTION "unable to bind server to host";
#define _UNABLE_TO_LISTEN_EXCEPTION "unable for server to listen on port";
#define _BAD_EPOLL_EXCETION "an error has occurred in epoll";

#define MAX_EVENTS 131072

namespace net {
    TCPNet::TCPNet(std::string host, unsigned int port) {
        this->host = host;
        this->port = port;
    }

    void TCPNet::_unblock(int fd) {
        int flags = fcntl(fd, F_GETFL, 0)
        if (flags == -1) throw "fcntl failed";
        flags |= O_NONBLOCK;
        if (fcntl(fd, F_SETFL, flags) == -1) throw "fcntl failed"; 
    }

    void TCPNet::serve() {
        this->should_run = true;
        struct sockaddr_in addr;
        int sock, addrLen;
        int opt = 1;
        void *buf[4096];
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == 0) throw _NO_SOCK_EXCEPTION;
        if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0) throw _UNABLE_TO_SHARE_ADDR_EXCEPTION;
        addr.sin_family = AF_INET;
        if (this->host.length() > 0 || this->host.compare("0.0.0.0") != 0) {
            inet_pton(AF_INET, (const char *)this->host, &addr.sin_addr.s_addr);
        } else {
            addr.sin_addr.s_addr = INADDR_ANY;
        }
        addr.sin_port = htons((uint32_t)port);
        if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) throw _UNABLE_TO_BIND_ADDR_EXCEPTION;
        this->_unblock(sock);
        if (listen(sock, SOMAXCONN) != 0) throw _UNABLE_TO_LISTEN_EXCEPTION;
        int evfd = epoll_create1(0);
        if (evfd == -1) {
            throw "epoll create failed";
        }
        struct epoll_event event;
        struct epoll_event events[];
        event.data.fd = sock;
        event.events = EPOLLIN|EPOLLET;
        if (epoll_ctl(evfd, EPOLL_CTL_ADD, sfd, &event) != 0) throw _BAD_EPOLL_EXCEPTION;
        events = calloc(MAX_EVENTS, sizeof(event));
        while (this->should_run) {
            int n;
            n = epoll_wait(efd, events, MAX_EVENTS, -1);
            for (int i = 0; i < n; i++) {
                // TODO handle error
                if (sfd == events[i].data.fd) {
                    for (;;) {
                        struct sockaddr in_addr;
                        socklen_t in_len = sizeof(in_addr);
                        char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];
                        int infd = accept(sfd, &in_addr, &in_len);
                        if (infd == -1) {
                            // TODO handle error
                        }
                        int success = getnameinfo(&in_addr, in_len, hbuf, sizeof(hbuf), sbuf, sizeof(sbuf), NI_NUMERICHOST, NI_NUMERICSERV);
                        if (success == 0) {
                            // TODO display success
                        }
                        this->unblock(infd);
                        continue;
                    }
                } else {
                    int done = 0;
                    for (;;) {
                        ssize_t count;
                        char buf[512];
                        count = read (events[i].data.fd, buf, sizeof buf);
                        if (count < 0) {
                            //TODO handle error
                        }
                        if (done == 1) {
                            close(events[i].data.fd);
                        }
                    }
                }
            }
        }
        free(events);
        close(sfd);
    }
}
