#ifndef __CCSDSPACKETWRAPPER_H
#define __CCSDSPACKETWRAPPER_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct CCSDSPacket CCSDSPacket;

CCSDSPacket* newCCSDSPacket(int apid, int packet_id);

void CCSDSPacket_SetSecondaryHeader(CCSDSPacket* v, void* data, unsigned int length);

void CCSDSPacket_PutInt32(CCSDSPacket* v, int i);

void CCSDSPacket_PutInt16(CCSDSPacket* v, unsigned short int i);

void CCSDSPacket_PutFloat(CCSDSPacket* v, float i);

unsigned char* CCSDSPacket_GetBuffer(CCSDSPacket* v);

int CCSDSPacket_GetLength(CCSDSPacket* v);

void CCSDSPacket_delete(CCSDSPacket* v);

#ifdef __cplusplus
}
#endif
#endif