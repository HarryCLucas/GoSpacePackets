#include "CCSDSPacket.hpp"
#include "CCSDSPacketWrapper.h"

extern "C" {
        CCSDSPacket* newCCSDSPacket(int apid, int packet_id) {
                return new CCSDSPacket(apid, packet_id);
        }

        void CCSDSPacket_PutInt32(CCSDSPacket* v, int i){
                v->putInt32(i);
        }

        void CCSDSPacket_PutInt16(CCSDSPacket* v, unsigned short int i) {
                v->putInt16(i);
        }

        void CCSDSPacket_SetSecondaryHeader(CCSDSPacket* v, void* data, unsigned int length) {
                v->setSecondaryHeader(data,length);
        }

        void CCSDSPacket_PutFloat(CCSDSPacket* v, float i) {
                v->putFloat(i);
        }

        unsigned char* CCSDSPacket_GetBuffer(CCSDSPacket* v) {
            return v->getBuffer();
        }

        int CCSDSPacket_GetLength(CCSDSPacket* v) {
            return v->getLength();
        }
            
        void CCSDSPacket_delete(CCSDSPacket* v){
                delete v;
        }
}