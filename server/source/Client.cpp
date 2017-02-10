#include "Client.h"
#include "Globals.h"
#include "network/packets/Packet2Message.h"
#include "network/packets/Packet0ServerIdentification.h"
#include "network/packets/Packet0ClientIdentification.h"
#include "network/packets/Packet1Ping.h"
#include "network/packets/Packet2Message.h"
#include "exceptions/ClientDisconnectedException.h"
#include <iostream>
#include <cstring>

Client::Client(SOCKET socket) : m_socket(socket), m_packetInputStream(socket), m_packetOutputStream(socket), m_identified(false), m_username() {
    m_inetAdress = Globals::server->m_serverNetwork->getInetAdress(m_socket);

    Packet0ServerIdentification iden(Globals::cfg->getServername());
    send(&iden);

    Packet2Message motd(Globals::cfg->getMotd());
    send(&motd);
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
            m_username = std::string(((Packet0ClientIdentification*) p)->getUsername());
            m_identified = true;
            std::cout << "client identified: " << m_username << std::endl;
            return;
        }
        else {
            //KICK THE PLAYER FROM THE SERVER
            delete p;
            return;
        }
    }

    if (dynamic_cast<Packet1Ping*>(p)) {
    }
    else if (dynamic_cast<Packet2Message*>(p)) {
        std::string message;
        message += getUsername();
        message += "> ";
        message += ((Packet2Message*) p)->getMessage();

        Packet2Message *packet_message = new Packet2Message(message);

        Globals::server->m_serverNetwork->broadcast(packet_message);

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

std::string Client::getUsername() {
    return m_username;
}

char *Client::getInetAdress() {
    return m_inetAdress;
}
