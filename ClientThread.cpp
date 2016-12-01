#include "ClientThread.h"

ClientThread::ClientThread(SOCKET socket) : m_socket(socket) {
}

int ClientThread::receive(char *buf, int len) {
    return recv(m_socket, buf, len, 0);
}

int ClientThread::send(char *buf, int len) {
    return send(m_socket, buff, len, 0);
}
