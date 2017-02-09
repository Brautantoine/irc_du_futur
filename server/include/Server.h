#ifndef SERVER_H
#define SERVER_H

#include "ServerNetwork.h"

#define SERVER_PROTOCOL_VERSION 0x1

class Server {
    public:
        ServerNetwork *m_serverNetwork;

        Server();
        ~Server();

        void loop();

        void broadcast(Packet *p);
};

#endif
