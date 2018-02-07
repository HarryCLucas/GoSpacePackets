#include <vector>
#include <arpa/inet.h>
#include <time.h>

class CCSDSPacket {
public:
    CCSDSPacket(int APID, int packetId);
    unsigned char* getBuffer();
    void setSecondaryHeader(void* data, unsigned int length);
    void putInt32(uint32_t value);
    void putInt16(uint16_t value);
    void putInt8(uint8_t value);
    void putFloat(float value);
    unsigned int getLength();
private:
    int apid;
    int packetId;
    std::vector<unsigned char>* dataBuffer;
    std::vector<unsigned char>* secondaryHeader;
    std::vector<unsigned char>* getPrimaryHeaderBuffer(uint16_t firstTwoBytes, uint32_t finalFourBytes);
    std::vector<unsigned char>* getSecondaryHeaderBuffer(uint32_t, uint8_t, uint8_t, uint32_t);
};