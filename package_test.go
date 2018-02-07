package CCSDSPacket

// #cgo LDFLAGS: -lccsds -L.
//
// #include <CCSDSPacketWrapper.h>

import (
	"testing"
)

func TestPacketLengthCorrect(t *testing.T) {
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

	if len(data) == 36 {
		t.Log("Correct packet length.")
	} else {
		t.Error("Package produced invalid packet length.")
	}
}
