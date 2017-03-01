package server

import (
	"fmt"
	"net"
	"strings"
	"sync"
	"sync/atomic"
)

type Server interface {
	Run() error
	Shutdown() error
	Connections() (int, error)
}

type tcpServer struct {
	Host        string
	Port        int
	Listener    *net.TCPListener
	isIPV6      bool
	shouldRun   bool
	handlers    map[int]*Handler
	connections []*net.TCPConn
	atomConns   atomic.Value
	runLock     *sync.Mutex
}

func newTCPServer(host string, port int) (*tcpServer, error) {
	return &tcpServer{
		Host:     host,
		Port:     port,
		FullAddr: fmt.Sprintf("%s:%d", host, port),
		isIPV6:   !strings.Contains(host, "."),
		runLock:  &sync.Mutex{},
	}
}

func (t *tcpServer) checkForStop() bool {
	t.runLock.Lock()
	defer t.runLock.Unlock()
	return !t.shouldRun
}

func (t *tcpServer) Run() error {
	netVer := "tcp4"
	if t.isIPV6 {
		netVer = "tcp6"
	}
	addr, err := net.ResolveTCPAddr(netVer)
	if err != nil {
		return err
	}
	t.Listener, err = net.ListenTCP(netVer, addr)
	if err != nil {
		return err
	}
	t.shouldRun = true
	for {
		if t.checkForStop() {
			return nil
		}
		conn := t.Listener.AcceptTCP()
		t.connections = append(t.connections, conn)
		t.atomConns.Store(t.connections)
		go t.delegate(conn)
	}
}

func (t *tcpServer) Shutdown() error {
	t.runLock.Lock()
	defer t.runLock.Unlock()
	t.shouldRun = false
}

func (t *tcpServer) Connections() int {
	conns := t.atomConns.Load()
	return len(conns)
}

func (t *tcpServer) delegate(conn *TCPConn) {
	// TODO
}

type udpServer struct{}

func newUDPServer(host string, port int) (*udpServer, error) {
	return &udpServer{
		Host: host,
		Port: port,
	}
}
