#include "network/packets/Packet.h"

#ifndef PACKET0_CLIENTIDENTIFICATION_H
#define PACKET0_CLIENTIDENTIFICATION_H

#include "network/DataInputStream.h"
#include <string>

#define MAX_USERNAME_LENGTH 32

class Packet0ClientIdentification : public Packet {
    private:
        std::string m_username;
    public:
        Packet0ClientIdentification(DataInputStream *dis);
        Packet0ClientIdentification(std::string username);

        std::string getUsername();
        virtual unsigned int getLength();
};

#endif
