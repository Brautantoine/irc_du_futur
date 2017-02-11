#include "network/packets/Packet3Disconnect.h"
#include "utils/NetworkUtils.h"
#include <cstring>

Packet3Disconnect::Packet3Disconnect(DataInputStream *dis) : Packet(0x3) {
    m_reason = dis->readString();
}
Packet3Disconnect::Packet3Disconnect(std::string reason) : Packet(0x3), m_reason(reason) {
    m_payload = new char[getLength()];

    char *reason_bytes = Packet::getBytes(m_reason);
    std::memcpy(m_payload, reason_bytes, NetworkUtils::getBytesLength(m_reason));
    delete reason_bytes;
}

std::string Packet3Disconnect::getReason() {
    return m_reason;
}

unsigned int Packet3Disconnect::getLength() {
    return NetworkUtils::getBytesLength(m_reason);
}
