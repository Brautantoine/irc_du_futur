#include "Packet.h"
#include <cstring> //for memcpy

Packet::Packet(char *buffer) : m_buffer(buffer) {
}

std::string Packet::getBuffer() {
    return m_buffer;
}
