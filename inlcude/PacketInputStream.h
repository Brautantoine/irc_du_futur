#ifndef PACKETINPUTSTREAM_H
#define PACKETINPUTSTREAM_H

#include <winsock2.h>
#include "Packet.h"

class PacketInputStream {
private:
    SOCKET m_socket;
public:
    PacketInputStream(SOCKET socket);

    Packet *nextPacket();
};

#endif // PACKETINPUTSTREAM_H
