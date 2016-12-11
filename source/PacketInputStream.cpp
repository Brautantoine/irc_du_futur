#include "PacketInputStream.h"
#include <iostream>
#include <cstring> //for memset

PacketInputStream::PacketInputStream(SOCKET socket) : m_socket(socket) {
}

Packet *PacketInputStream::nextPacket() {
    char recvbuf[PACKET_SIZE];
    memset(recvbuf, 0, sizeof(recvbuf));

    int bytesReceived = recv(m_socket, recvbuf, PACKET_SIZE, 0);

    if (bytesReceived > 0) {
        std::cout << "Bytes received: " << bytesReceived << ": " << recvbuf << " from: "<< m_socket << std::endl;
        return new Packet(recvbuf);
    }
    else if (bytesReceived == 0) {
        std::cout << "Connection closed" << std::endl;
        return nullptr;
    }
    else {
        std::cout << "recv failed: " << WSAGetLastError() << std::endl;
        return nullptr;
    }
}
