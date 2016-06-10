package network

import (
	"net"
)

func HandleRespError(conn net.Conn, err error) {
	strErr := err.Error()
	conn.Write(([]byte)(strErr))
}
