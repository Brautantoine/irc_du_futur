#include "network/packets/Packet1Ping.h"

Packet1Ping::Packet1Ping() : Packet(0x1) {
}

unsigned int Packet1Ping::getLength() {
    return 0;
}
