#include "ServerClient.h"
#include "Globals.h"
#include "network/packets/Packet2Message.h"
#include "network/packets/Packet0ServerIdentification.h"
#include "network/packets/Packet0ClientIdentification.h"
#include "network/packets/Packet1Ping.h"
#include "network/packets/Packet2Message.h"
#include "network/packets/Packet3Disconnect.h"
#include "exceptions/ClientDisconnectedException.h"
#include <iostream>
#include <cstring>

Client::Client(SOCKET socket) : m_socket(socket), m_packetInputStream(socket), m_packetOutputStream(socket), m_identified(false), m_username() {
    m_inetAdress = Globals::server->m_serverNetwork->getInetAdress(m_socket);

    Packet0ServerIdentification iden(Globals::cfg->getServername());
    send(&iden);
}

Client::~Client() {
    shutdown(m_socket, SD_BOTH);
    closesocket(m_socket);
}

void Client::update() {
    if (!m_packetInputStream.hasPacket()) {
        return;
    }

    Packet *p = m_packetInputStream.nextPacket();

    if (!m_identified) {
        if (dynamic_cast<Packet0ClientIdentification*>(p)) {
            if (((Packet0ClientIdentification*) p)->getProtocol() != Globals::PROTOCOL_VERSION) {
                delete p;
                kick("Ur using different protocol! you:" + std::to_string(((Packet0ClientIdentification*) p)->getProtocol()) + " me:" + std::to_string(Globals::PROTOCOL_VERSION));
                return;
            }

            m_username = std::string(((Packet0ClientIdentification*) p)->getUsername());
            m_identified = true;
            std::cout << "client identified: " << m_username << std::endl;

            Packet2Message motd(Globals::cfg->getMotd());
            send(&motd);

            return;
        }
        else {
            delete p;
            kick("U need to show me ur id papers (packet0), go away");
            return;
        }
    }

    if (dynamic_cast<Packet1Ping*>(p)) {
    }
    else if (dynamic_cast<Packet2Message*>(p)) {
        std::string message(((Packet2Message*) p)->getMessage());

        Packet2Message *packet_message = new Packet2Message(message);
        Globals::server->m_serverNetwork->broadcast(packet_message);

        EventMessage e(this, message);
        Globals::scriptManager->callEvent(&e);

        delete packet_message;
    }
    else {
        std::cout << "unknown packet" << std::endl;
    }

    delete p;
}

void Client::send(Packet *packet) {
    try {
        m_packetOutputStream.writePacket(packet);
    }
    catch (const std::exception &e) {
        Globals::server->m_serverNetwork->removeClient(this);
    }
}

void Client::kick(std::string reason) {
    Packet3Disconnect packet(reason);
    send(&packet);
    Globals::server->m_serverNetwork->removeClient(this);
}

std::string Client::getUsername() {
    return m_username;
}

char *Client::getInetAdress() {
    return m_inetAdress;
}
