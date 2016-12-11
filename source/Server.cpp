#include "Server.h"
#include "Client.h"
#include <algorithm> //for vector remove
#include <iostream>
#include <thread>

Server::Server() : m_clients() {
}

SOCKET Server::waitForConnection() {
    SOCKET TempSock = SOCKET_ERROR;

    while (TempSock == SOCKET_ERROR) {
        TempSock = accept(m_serverSocket, NULL, NULL);

        if (TempSock != SOCKET_ERROR)
            return TempSock;
    }
}

void Server::listen() {
    while (1) {
        SOCKET socket = waitForConnection();

        Client *client = new Client(socket, this);

        addClient(client);
    }
}

void Server::removeClient(Client *client) {
    m_clients.erase(std::remove(m_clients.begin(), m_clients.end(), client), m_clients.end());
    delete client;

    std::cout << "Client removed!\n";
}

void Server::addClient(Client *client) {
    m_clients.push_back(client);

    std::cout << "Client added!\n";
}

void Server::close() {
    for (Client *client : m_clients) //DANGER ?
        delete client;
    m_clients.clear();
    WSACleanup();
}

void Server::start() {
    WSADATA WsaDat;
    if(WSAStartup(MAKEWORD(2,2), &WsaDat) != 0) {
        std::cout << "WSA Initialization failed!\r\n";
        close();
        return;
    }

    m_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_serverSocket == INVALID_SOCKET) {
        std::cout<<"Socket creation failed.\r\n";
        close();
        return;
    }

    SOCKADDR_IN serverInf;
    serverInf.sin_family = AF_INET;
    serverInf.sin_addr.s_addr = INADDR_ANY;
    serverInf.sin_port = htons(8888);

    if(bind(m_serverSocket, (SOCKADDR*)(&serverInf), sizeof(serverInf)) == SOCKET_ERROR) {
        std::cout << "Unable to bind socket!\r\n";
        close();
        return;
    }

    ::listen(m_serverSocket, 1);

    std::thread t(&Server::listen, this);
    t.join();
}

void Server::broadcast(const char *buffer) {
    for (auto *client : m_clients) {
        client->send(buffer);
    }
}
