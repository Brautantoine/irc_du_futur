#ifndef PACKET3_DISCONNECT_H
#define PACKET3_DISCONNECT_H

#include "network/packets/Packet.h"
#include "network/DataInputStream.h"
#include <string>

class Packet3Disconnect : public Packet {
    private:
        std::string m_reason;
    public:
        Packet3Disconnect(DataInputStream *dis);
        Packet3Disconnect(std::string reason);

        std::string getReason();

        virtual unsigned int getLength() override;
};

#endif
