#include "Server.h"
#include "Client.h"
#include <chrono>
#include <thread>

Server::Server() {
    m_serverNetwork = new ServerNetwork();
}

Server::~Server() {
    delete m_serverNetwork;
}

void Server::loop() {
    while (1) {
        m_serverNetwork->acceptNewClient();

        for (Client *client : m_serverNetwork->m_clients) {
            client->update();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(25)); //approx 40 ticks per second
    }
}
