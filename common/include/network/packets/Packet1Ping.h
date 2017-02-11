#ifndef PACKET1_PING_H
#define PACKET1_PING_H

#include "network/packets/Packet.h"

class Packet1Ping : public Packet {
    public:
        Packet1Ping();

        virtual unsigned int getLength() override;
};

#endif
