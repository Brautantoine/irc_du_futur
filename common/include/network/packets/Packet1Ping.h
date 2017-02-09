#include "network/packets/Packet.h"

#ifndef PACKET1_PING_H
#define PACKET1_PING_H

class Packet1Ping : public Packet {
    public:
        Packet1Ping();

        virtual unsigned int getLength();
};

#endif
