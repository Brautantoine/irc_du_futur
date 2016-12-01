#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED

#include "Packet.h"
#include "ClientThread.h"
#include "ConnectionThread.h"
#include <vector>

class Server {
public:
    Server(int port);
    ~Server();
    void sendToAll(Packet packet);
    void sendTo(int clientId);
private:
    int port;
    ConnectionThread m_connThread;
    std::vector<ClientThread> m_clients;
};

#endif // SERVER_H_INCLUDED
