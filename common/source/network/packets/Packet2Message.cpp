#include "network/packets/Packet2Message.h"
#include "utils/NetworkUtils.h"
#include <cstring>

Packet2Message::Packet2Message(DataInputStream *dos) : Packet(0x2) {
    m_message = dos->readString();
}

Packet2Message::Packet2Message(std::string message) : Packet(0x2), m_message(message) {
    m_payload = new char[getLength()];

    char *message_bytes = Packet::getBytes(m_message);
    std::memcpy(m_payload, message_bytes, NetworkUtils::getBytesLength(m_message));
    delete message_bytes;
}

std::string Packet2Message::getMessage() {
    return m_message;
}

unsigned int Packet2Message::getLength() {
    return NetworkUtils::getBytesLength(m_message);
}
