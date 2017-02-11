#ifndef SERVER_H
#define SERVER_H

#include "ServerNetwork.h"

class Server {
    public:
        ServerNetwork *m_serverNetwork;

        Server();
        ~Server();

        void loop();

        void broadcast(Packet *p);
};

#endif
