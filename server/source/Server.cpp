#include "Server.h"
#include "Client.h"
#include "exceptions/ClientDisconnectedException.h"
#include "ConfigurationServer.h"
#include "network/packets/Packet.h"
#include "Globals.h"
#include <chrono>
#include <thread>
#include <iostream>

Server::Server() {
    m_serverNetwork = new ServerNetwork();
    std::string filename("server.cfg");
    Globals::cfg = new ConfigurationServer(filename);
}

Server::~Server() {
    delete m_serverNetwork;
}

void Server::loop() {
    while (1) {
        m_serverNetwork->acceptNewClient();

        for (Client *client : m_serverNetwork->m_clients) {
            try {
                client->update();
            }
            catch (const ClientDisconnectedException &e) {
                m_serverNetwork->removeClient(client);
            }
            catch (const std::exception &e) {
                std::cout << e.what() << std::endl;
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(25)); //approx 40 ticks per second
    }
}

void Server::broadcast(Packet *p) {
    for (Client *client : m_serverNetwork->m_clients) {
        try {
            client->send(p);
        }
        catch (const ClientDisconnectedException &e) {
            m_serverNetwork->removeClient(client);
        }
        catch (const std::exception &e) {
            std::cout << e.what() << std::endl;
        }
    }
}
