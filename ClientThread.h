#ifndef CLIENTTHREAD_H_INCLUDED
#define CLIENTTHREAD_H_INCLUDED

#include <winsock2.h>

class ClientThread {
public:
    ClientThread(SOCKET socket);
    int receive();
    int send();
private:
    SOCKET m_socket;
};

#endif // CLIENTTHREAD_H_INCLUDED
