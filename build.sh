#!/bin/bash
cd ./CCSDSPacket

g++ -fPIC -c CCSDSPacket.cpp -o CCSDSPacket.o
g++ -fPIC -c CCSDSPacketWrapper.cc -o Wrapper.o
g++ -fPIC -shared -o libccsds.so Wrapper.o CCSDSPacket.o

rm Wrapper.o CCSDSPacket.o
mv libccsds.so ../libccsds.so

cd ..

sudo cp libccsds.so /usr/lib/libccsds.so
sudo ldconfig