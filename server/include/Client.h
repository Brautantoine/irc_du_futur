#ifndef CLIENT_H
#define CLIENT_H

#include "network/packets/Packet.h"
#include "network/PacketInputStream.h"
#include "network/PacketOutputStream.h"
#include <winsock2.h>
#include <string>

class Client {
    private:
        SOCKET m_socket;
        PacketInputStream m_packetInputStream;
        PacketOutputStream m_packetOutputStream;

        std::string m_username;
    public:
        Client(SOCKET socket);
        ~Client();

        void update();
        void send(Packet *packet);

        std::string getUsername();
};

#endif // CLIENT_H
