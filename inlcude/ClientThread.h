#ifndef CLIENTTHREAD_H_INCLUDED
#define CLIENTTHREAD_H_INCLUDED

#include <winsock2.h>

class ClientThread {
public:
    ClientThread(SOCKET socket);
    int receive(char *buf, int len);
    int send(char *buf, int len);
private:
    SOCKET m_socket;
};

#endif // CLIENTTHREAD_H_INCLUDED
