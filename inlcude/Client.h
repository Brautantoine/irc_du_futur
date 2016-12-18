#ifndef CLIENT_H
#define CLIENT_H

#include "Packet.h"
#include <winsock2.h>

class Client {
private:
    SOCKET m_socket;
public:
    Client(SOCKET socket);
    ~Client();

    void update();
    void send(Packet *packet);
};

#endif // CLIENT_H
