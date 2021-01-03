package main

import (
	"net"
)

const (
	maxBuffer int = 5000
)

var (
	conn net.Conn = nil
)

func connect() {
	var err error
	conn, err = net.Dial("tcp", ":8000")
	if err != nil {
		panic(err)
	}
}

func send(path string) {
	return
}
