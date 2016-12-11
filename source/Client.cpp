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

        Packet *message = new Packet(packet->getBuffer());
        m_server->broadcast(message);
        delete message;

        delete packet;
    }

    m_server->removeClient(this); //Delete this client
}

Client::Client(SOCKET socket, Server *server) : m_socket(socket), m_pis(socket), m_server(server) {
    std::thread m_pis_thread(&Client::loop, this);
    m_pis_thread.detach();
}
Client::~Client() {
    shutdown(m_socket, SD_SEND);
    closesocket(m_socket);
}

void Client::send(Packet *packet) {
    std::cout << "sending " << packet->getBuffer() << "\n";
    ::send(m_socket, packet->getBuffer(), packet->getLength(), 0);
}
