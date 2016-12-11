#ifndef CLIENT_H
#define CLIENT_H

#include "PacketInputStream.h"
#include <winsock2.h>
#include <thread>

class Server; //Forward declaration

class Client {
private:
    SOCKET m_socket;
    std::thread m_pis_thread;
    PacketInputStream m_pis;
    Server *m_server;

    void loop();
public:
    Client(SOCKET socket, Server *server);
    ~Client();

    void send(Packet *packet);
};

#endif // CLIENT_H
