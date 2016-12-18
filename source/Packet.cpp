#include "Packet.h"
#include <cstring> //for memcpy

Packet::Packet(char *buffer) : m_buffer(buffer), m_length(strlen(buffer)) {
}

Packet::~Packet() {
    delete m_buffer;
}

const char *Packet::getBuffer() {
    return m_buffer;
}

const int Packet::getLength() {
    return m_length;
}
