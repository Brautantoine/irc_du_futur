#ifndef PACKET0_CLIENTIDENTIFICATION_H
#define PACKET0_CLIENTIDENTIFICATION_H

#include "network/packets/Packet.h"
#include "network/DataInputStream.h"
#include <string>

#define MAX_USERNAME_LENGTH 32

class Packet0ClientIdentification : public Packet {
    private:
        std::string m_username;
        unsigned int short m_protocol;
    public:
        Packet0ClientIdentification(DataInputStream *dis);

        unsigned int short getProtocol();
        std::string getUsername();
        virtual unsigned int getLength() override;
};

#endif
