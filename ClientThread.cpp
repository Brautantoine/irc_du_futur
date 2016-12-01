    #include "ClientThread.h"

    ClientThread::ClientThread(SOCKET socket) : m_socket(socket) {
    }

    int ClientThread::receive() {
        return recv();
    }
    int ClientThread::send() {
    }
