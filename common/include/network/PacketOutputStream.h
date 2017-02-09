#ifndef PACKETOUTPUTSTREAM_H
#define PACKETOUTPUTSTREAM_H

#include <winsock2.h>
#include "network/packets/Packet.h"
#include "network/DataOutputStream.h"

class PacketOutputStream {
    private:
        DataOutputStream m_dataOutputStream;
    public:
        PacketOutputStream(DataOutputStream dos);
        ~PacketOutputStream();

        void writePacket(Packet *packet);
};

#endif
