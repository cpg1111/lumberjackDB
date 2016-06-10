package main

import (
	"flag"
	"fmt"
	"net"

	"github.com/cpg1111/LumberjackDB/db/network"
)

var (
	serverType = flag.String("server-type", "tcp", "Protocol to serve on, defaults to TCP")
	host       = flag.String("host", "127.0.0.1", "Host to serve on, defaults to 127.0.0.1")
	port       = flag.String("port", "9898", "Port to serve on, defaults to 9898")
	handlers   = make(map[string]func(conn net.Conn) error)
)

func handler(conn net.Conn) {
	defer conn.Close()
	for i := range handlers {
		err := handlers[i](conn)
		if err != nil {
			network.HandleRespError(conn, err)
			break
		}
	}
}

func main() {
	flag.Parse()
	addr := fmt.Sprintf("%s:%s", *host, *port)
	network.Init(*serverType, addr, handler)
}
