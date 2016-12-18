#include "Client.h"
#include "Globals.h"
#include <iostream>
#include <cstring>

Client::Client(SOCKET socket) : m_socket(socket) {
    Packet welcome("Welcome to the server"); //Force tty resize to 50 columns 100 rows
    send(&welcome);
}

Client::~Client() {
    shutdown(m_socket, SD_BOTH);
    closesocket(m_socket);
}

void Client::update() {
    char *temp = new char[PACKET_SIZE];
    memset(temp, 0, sizeof(char)*PACKET_SIZE);
    int bytesReceived = recv(m_socket, temp, PACKET_SIZE-1, 0);
    temp[strlen(temp)] = '\0'; //Force add char null terminator

    int error = WSAGetLastError();

    if (error == WSAEWOULDBLOCK || bytesReceived == -1) { //Nothing received
        return;
    }
    else if (error == 0 && bytesReceived == 0) { //Connection closed
        Globals::server->m_serverNetwork->removeClient(this);
        delete temp;
        return;
    }
    else if (bytesReceived > 0) { //Data received
        Packet *packet = new Packet(temp);
        Globals::server->m_serverNetwork->broadcast(packet);
        delete packet;
    }
}

void Client::send(Packet *packet) {
    int result = ::send(m_socket, packet->getBuffer(), packet->getLength(), 0);
    if (result == -1)
        Globals::server->m_serverNetwork->removeClient(this);
}
