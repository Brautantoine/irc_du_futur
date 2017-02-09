#ifndef SERVERNETWORK_H
#define SERVERNETWORK_H

#include "network/packets/Packet.h"
#include "Client.h"
#include <winsock2.h>
#include <vector>

class ServerNetwork {
    private:
        SOCKET m_serverSocket;
    public:
        std::vector<Client*> m_clients;

        ServerNetwork();
        ~ServerNetwork();

        bool acceptNewClient();

        void removeClient(Client *client);
        void addClient(Client *client);

        void broadcast(Packet *packet);
};
#endif
