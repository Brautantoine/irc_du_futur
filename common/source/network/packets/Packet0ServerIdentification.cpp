#include "network/packets/Packet0ServerIdentification.h"
#include "utils/NetworkUtils.h"
#include <cstring>

Packet0ServerIdentification::Packet0ServerIdentification(std::string servername) : Packet(0x0), m_servername(servername) {
    m_payload = new char[getLength()];

    char *servername_bytes = Packet::getBytes(m_servername);
    std::memcpy(m_payload, servername_bytes, NetworkUtils::getBytesLength(m_servername));
    delete servername_bytes;
}

std::string Packet0ServerIdentification::getServername() {
    return m_servername;
}

unsigned int Packet0ServerIdentification::getLength() {
    return NetworkUtils::getBytesLength(m_servername);
}
