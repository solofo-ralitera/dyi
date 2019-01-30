package main

import (
	"log"
	"time"

	"github.com/jacobsa/go-serial/serial"
)

func main() {
	// Set up options.
	options := serial.OpenOptions{
		PortName:        "/dev/ttyUSB0",
		BaudRate:        19200,
		DataBits:        8,
		StopBits:        1,
		MinimumReadSize: 4,
	}

	// Open the port.
	port, err := serial.Open(options)
	if err != nil {
		log.Fatalf("serial.Open: %v", err)
	}

	// Make sure to close it later.
	defer port.Close()

	port.Write([]byte("r1000\n"))
	time.Sleep(100 * time.Millisecond)
	port.Write([]byte("r2000\n"))
	time.Sleep(100 * time.Millisecond)
	port.Write([]byte("r3000\n"))
	time.Sleep(100 * time.Millisecond)
	port.Write([]byte("r4000\n"))
	time.Sleep(100 * time.Millisecond)
	port.Write([]byte("r5000\n"))
	time.Sleep(100 * time.Millisecond)
	port.Write([]byte("r6000\n"))
	time.Sleep(100 * time.Millisecond)

}
