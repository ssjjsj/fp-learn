package main

import (
	"fmt"
	"net"
)

func main() {
	ln, err := net.Listen("tcp", ":1234")
	if err != nil {
	// handle error
	}
	
	for {
		conn, err := ln.Accept()
		if err != nil {
		// handle error
		}
		go handleConnection(conn)
	}
}

func handleConnection(conn net.Conn){
     bytes = byte[1024]
	 n, err = conn.read(bytes)
	 s := string(bytes[:n])
	 fmt.print
}