#include "Client.h"
#include "Server.h"
#include "Packet.h"

#include <iostream>

void Client::loop() {
    while (1) {
        Packet *packet = m_pis.nextPacket();

        if (packet == nullptr) {
            break;
        }

        m_server->broadcast(packet->getBuffer().c_str());

        delete packet;
    }

    m_server->removeClient(this); //Delete this client
}

Client::Client(SOCKET socket, Server *server) : m_socket(socket), m_pis(socket), m_server(server) {
    std::thread m_pis_thread(&Client::loop, this);
    m_pis_thread.detach();
}
Client::~Client() {
    closesocket(m_socket);
}

void Client::send(const char *buffer) {
    std::cout << "sending " << buffer << "\n";
    ::send(m_socket, buffer, strlen(buffer), 0);
}
