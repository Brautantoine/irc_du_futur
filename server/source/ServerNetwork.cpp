#include "ServerNetwork.h"

#include "Globals.h"
#include <algorithm>
#include <iostream>

ServerNetwork::ServerNetwork() {
    WSADATA WsaData;
    if(WSAStartup(MAKEWORD(2,2), &WsaData) != 0) {
        std::cout << "WSA Initialization failed!\n";
        exit(1);
    }

    m_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_serverSocket == INVALID_SOCKET) {
        std::cout << "Socket creation failed\n";
        WSACleanup();
        exit(1);
    }

    //Set socket to non-blocking
    u_long iMode=1;
    ioctlsocket(m_serverSocket, FIONBIO, &iMode);

    SOCKADDR_IN serverInfo;
    serverInfo.sin_family = AF_INET;
    serverInfo.sin_addr.s_addr = INADDR_ANY;
    serverInfo.sin_port = htons(8888);

    if(bind(m_serverSocket, (SOCKADDR*)(&serverInfo), sizeof(serverInfo)) == SOCKET_ERROR) {
        std::cout << "Unable to bind socket!\n";
        closesocket(m_serverSocket);
        WSACleanup();
        exit(1);
    }

    if (listen(m_serverSocket, 1) == SOCKET_ERROR) {
        std::cout << "Unable to listen socket!\n";
        closesocket(m_serverSocket);
        WSACleanup();
        exit(1);
    }
}

ServerNetwork::~ServerNetwork() {
    for (Client *client : m_clients) //DANGER ?
        removeClient(client);
    m_clients.clear();
    WSACleanup();
}

bool ServerNetwork::acceptNewClient() {
    SOCKET TempSock = accept(m_serverSocket, nullptr, nullptr);

    if (TempSock == INVALID_SOCKET) {
        return false;
    }

    //Set socket to non-blocking
    u_long iMode=1;
    ioctlsocket(TempSock, FIONBIO, &iMode);

    Client *client = new Client(TempSock);
    if (m_clients.size() >= Globals::cfg->getMaxConnections()) {
        client->kick("Server is full!");
        return false;
    }

    addClient(client);
    return true;
}

char *ServerNetwork::getInetAdress(SOCKET socket) {
    struct sockaddr_in client_info;
    int addrsize = sizeof(client_info);

    getpeername(socket, (struct sockaddr*)&client_info, &addrsize);

    return inet_ntoa(client_info.sin_addr);
}

void ServerNetwork::broadcast(Packet *packet) {
    for (Client *client : m_clients) {
        client->send(packet);
    }
}

void ServerNetwork::removeClient(Client *client) {
    m_clients.erase(std::remove(m_clients.begin(), m_clients.end(), client), m_clients.end());

    std::cout << "closed connection " << client->getInetAdress() << std::endl;
    delete client;
}

void ServerNetwork::addClient(Client *client) {
    m_clients.push_back(client);

    std::cout << "new connection from " << client->getInetAdress() << std::endl;
}
