package network

import (
	"log"
	"net"

	"github.com/golang/protobuf/proto"
)

var _ = proto.WireBytes // TODO handle protobufs

type Handler func(conn net.Conn)

func Init(srvType, addr string, handler Handler) error {
	srv, srvErr := net.Listen(srvType, addr)
	if srvErr != nil {
		return srvErr
	}
	defer srv.Close()
	log.Println("Lumberjack is chopping away on ", addr)
	for {
		conn, connErr := srv.Accept()
		if connErr != nil {
			return connErr
		}
		go handler(conn)
	}
}
