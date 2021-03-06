A Golang-accessible packet crafter for the CCSDS protocol. 

There is a C++ backend for building CCSDS packets according to the Space Data Protocol paper released by the CCSDS consortium. 

This C++ codebase is wrapped into a C library. The C library is called by Golang through CGO to enable people to make use of the ease of Golang for writing CCSDS packets without having to worry about the details of crafting the packets themselves.

To build the library, simply run build.sh. An example program is available below. This program simply opens a UDP connection to local port 10200, and sends a CCSDS packet to the port once per second:

```go
package main

// #cgo LDFLAGS: -lccsds -L.
//
// #include <CCSDSPacketWrapper.h>

import (
	"fmt"
	"net"
	"time"
	"GoSpacePackets"
)

func main(t *testing.T) {

	ServerAddr, err := net.ResolveUDPAddr("udp", "127.0.0.1:10200")
	LocalAddr, err := net.ResolveUDPAddr("udp", "127.0.0.1:1000")
	Conn, err := net.DialUDP("udp", LocalAddr, ServerAddr)

	if err != nil {
		fmt.Println(err.Error())
	}

	for {

		packet := new(CCSDSPacket)
		packet.NewCCSDSPacket(1, 33)

		str := "Heyyo!"
		bytes := []byte(str)
		packet.SetSecondaryHeader(bytes)
		packet.PutFloat(2.5)
		packet.PutFloat(-1.923)
		packet.PutInt32(12)
		packet.PutInt32(-10)
		packet.PutInt16(-10)
		packet.PutInt16(50)
		packet.PutFloat(10)
		data := packet.GetBuffer()

		fmt.Printf("Writing %v bytes", len(data))

		_, _ = Conn.Write(data)
		time.Sleep(time.Second * 1)
	}
}
```