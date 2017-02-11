#include "network/packets/Packet0ClientIdentification.h"
#include "utils/NetworkUtils.h"
#include <cstring>
#include <iostream>

Packet0ClientIdentification::Packet0ClientIdentification(DataInputStream *dis) : Packet(0x0) {
    m_protocol = dis->readByte();
    m_username = dis->readString();
}

std::string Packet0ClientIdentification::getUsername() {
    return m_username;
}

unsigned int short Packet0ClientIdentification::getProtocol() {
    return m_protocol;
}

unsigned int Packet0ClientIdentification::getLength() {
    return NetworkUtils::getBytesLength(m_username);
}
