#include "network/packets/Packet0ClientIdentification.h"
#include "utils/NetworkUtils.h"
#include <cstring>
#include <iostream>

Packet0ClientIdentification::Packet0ClientIdentification(DataInputStream *dis) : Packet(0x0) {
    m_username = dis->readString();
}

Packet0ClientIdentification::Packet0ClientIdentification(std::string username) : Packet(0x0), m_username(username) {
    m_payload = new char[getLength()];

    char *username_bytes = Packet::getBytes(m_username);
    std::memcpy(m_payload, username_bytes, NetworkUtils::getBytesLength(m_username));
    delete username_bytes;
}

std::string Packet0ClientIdentification::getUsername() {
    return m_username;
}

unsigned int Packet0ClientIdentification::getLength() {
    return NetworkUtils::getBytesLength(m_username);
}
