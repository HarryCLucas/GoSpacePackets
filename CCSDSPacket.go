package GoSpacePackets

// #cgo LDFLAGS: -lccsds -L.
//
// #include "CCSDSPacketWrapper.h"
import "C"
import "unsafe"

type CCSDSPacket struct {
	packet *(C.struct_CCSDSPacket)
}

func (obj *CCSDSPacket) NewCCSDSPacket(apid int, packetid int) {
	obj.packet = C.newCCSDSPacket(C.int(apid), C.int(packetid))
}

func (obj *CCSDSPacket) SetSecondaryHeader(data []byte) {
	C.CCSDSPacket_SetSecondaryHeader(obj.packet, C.CBytes(data), C.uint(len(data)))
}

func (obj *CCSDSPacket) PutInt32(value int32) {
	C.CCSDSPacket_PutInt32(obj.packet, C.int(value))
}

func (obj *CCSDSPacket) PutInt16(value int16) {
	C.CCSDSPacket_PutInt16(obj.packet, C.ushort(value))
}

func (obj *CCSDSPacket) PutFloat(value float32) {
	C.CCSDSPacket_PutFloat(obj.packet, C.float(value))
}

func (obj *CCSDSPacket) GetBuffer() []byte {

	var pnt unsafe.Pointer
	pnt = unsafe.Pointer(C.CCSDSPacket_GetBuffer(obj.packet))
	bufferLength := int(C.CCSDSPacket_GetLength(obj.packet))
	result := make([]byte, bufferLength)
	for i := 0; i < bufferLength; i++ {
		var uchar C.uchar
		result[i] = *(*byte)(unsafe.Pointer(uintptr(pnt) + uintptr(i)*uintptr(unsafe.Sizeof(uchar))))
	}
	return result
}
