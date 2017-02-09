#ifndef PACKETINPUTSTREAM_H
#define PACKETINPUTSTREAM_H

#include <winsock2.h>
#include "network/packets/Packet.h"
#include "network/DataInputStream.h"

class PacketInputStream {
    private:
        DataInputStream m_dataInputStream;
        char m_currentId;
    public:
        PacketInputStream(DataInputStream dis);
        ~PacketInputStream();

        Packet *nextPacket();
        bool hasPacket();
};

#endif
