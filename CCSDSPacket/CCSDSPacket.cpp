#include "CCSDSPacket.hpp"

const uint16_t VERSION_NUMBER = 0;
const uint16_t TYPE = 0;
const uint16_t SEQUENCE_FLAGS = 3;
const uint16_t PACKET_SEQUENCE = 0;
const uint8_t TIME_ID = 0;
const uint8_t PACKET_TYPE = 0;
const uint16_t PRIMARY_HEADER_LENGTH = 6;
const uint8_t CHECKSUM_PRESENT = 0;

uint16_t SECONDARY_HEADER_FLAG = 0; 
uint16_t SECONDARY_HEADER_LENGTH = 0;

CCSDSPacket::CCSDSPacket(int ap_id, int packet_id){
    if (ap_id> 2048|| ap_id < 0){
        return;
    }
    if (packet_id > 4294967296 || packet_id < 0){
        return;
    }

    dataBuffer = new std::vector<unsigned char>();
    this->apid = ap_id;
    this->packetId = packet_id;
}

unsigned char* CCSDSPacket::getBuffer(){

    uint16_t ph_firstTwoBytes = (VERSION_NUMBER<< 5) | (PACKET_TYPE << 4) | (SECONDARY_HEADER_FLAG << 3) | (this->apid << 8);

    uint32_t packetDataLength = htons(SECONDARY_HEADER_LENGTH + dataBuffer->size()-1);
    uint32_t ph_finalFourBytes = (SEQUENCE_FLAGS << 6) | (PACKET_SEQUENCE << 8) | (packetDataLength << 16);
    std::vector<unsigned char>* result = getPrimaryHeaderBuffer(ph_firstTwoBytes, ph_finalFourBytes);

    if (SECONDARY_HEADER_FLAG == 1){
        result->insert(result->end(), this->secondaryHeader->begin(), this->secondaryHeader->end());
    }
    result->insert(result->end(), dataBuffer->begin(), dataBuffer->end());

    return result->data();
}

unsigned int CCSDSPacket::getLength(){
    return SECONDARY_HEADER_LENGTH + PRIMARY_HEADER_LENGTH + dataBuffer->size();
}

void CCSDSPacket::setSecondaryHeader(void* data, unsigned int length){
    if (length < 1){
        SECONDARY_HEADER_FLAG = 0;
        SECONDARY_HEADER_LENGTH = 0;
        delete secondaryHeader;
        secondaryHeader = NULL;
        return;
    }
    std::vector<unsigned char>* result = new std::vector<unsigned char>();
    SECONDARY_HEADER_FLAG = 1;
    SECONDARY_HEADER_LENGTH = length;

    for (int i = 0; i < length; i++){
        unsigned char* point = (unsigned char*) (data);
        result->push_back(*(point+i));
    }
    secondaryHeader = result;
}

void CCSDSPacket::putFloat(float value){
    unsigned char* pointer = (unsigned char*)&value;
    dataBuffer->push_back(*(pointer+3));
    dataBuffer->push_back(*(pointer+2));
    dataBuffer->push_back(*(pointer+1));
    dataBuffer->push_back(*(pointer));
}

void CCSDSPacket::putInt32(uint32_t value){
    unsigned char* pointer = (unsigned char*)&value;
    dataBuffer->push_back(*(pointer+3));
    dataBuffer->push_back(*(pointer+2));
    dataBuffer->push_back(*(pointer+1));
    dataBuffer->push_back(*(pointer));
}

void CCSDSPacket::putInt16(uint16_t value){
    unsigned char* pointer = (unsigned char*)&value;
    dataBuffer->push_back(*(pointer+1));
    dataBuffer->push_back(*(pointer));
}

void CCSDSPacket::putInt8(uint8_t value){
    unsigned char* pointer = (unsigned char*)&value;
    dataBuffer->push_back(*(pointer+1));
    dataBuffer->push_back(*(pointer));
}

std::vector<unsigned char>* CCSDSPacket::getPrimaryHeaderBuffer(uint16_t firstTwoBytes, uint32_t finalFourBytes){
    std::vector<unsigned char>* packetHeader = new std::vector<unsigned char>();
    unsigned char* pointer = (unsigned char*)&firstTwoBytes;
    packetHeader->push_back(*pointer);
    packetHeader->push_back(*(pointer+1));

    pointer = (unsigned char*)&finalFourBytes;
    packetHeader->push_back(*pointer);
    packetHeader->push_back(*(pointer+1));
    packetHeader->push_back(*(pointer+2));
    packetHeader->push_back(*(pointer+3));
    return packetHeader;
}
