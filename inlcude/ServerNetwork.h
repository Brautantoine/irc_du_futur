#ifndef SERVERNETWORK_H
#define SERVERNETWORK_H

#include "Packet.h"
#include <winsock2.h>
#include "Client.h"
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
