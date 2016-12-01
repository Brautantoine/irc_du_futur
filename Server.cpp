#include "Server.h"

Server::Server(int port) : m_port(port) {
}

void Server::sendToAll(Packet packet) {
    for (int i = 0 ; i < clients.size() ; i++) {
        send(clients[i].m_socket, packet.getBuf(), packet.getSize(), 0);
    }
}

void Server::sendTo(int clientId) {
}
