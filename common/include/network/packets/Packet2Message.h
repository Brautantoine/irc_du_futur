#include "network/packets/Packet.h"

#ifndef PACKET2_MESSAGE_H
#define PACKET2_MESSAGE_H

#include "network/DataInputStream.h"
#include <string>

#define MAX_MESSAGE_LENGTH 10000

class Packet2Message : public Packet {
    private:
        std::string m_message;
    public:
        Packet2Message(DataInputStream *dis);
        Packet2Message(std::string message);

        std::string getMessage();

        virtual unsigned int getLength();
};

#endif
