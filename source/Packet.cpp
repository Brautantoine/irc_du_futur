#include "Packet.h"
#include <cstring> //for memcpy

Packet::Packet(char *buffer) : m_buffer(buffer), m_length(strlen(buffer)) {
}
Packet::~Packet() {
    delete m_buffer;
}

char *Packet::getBuffer() {
    return m_buffer;
}

int Packet::getLength() {
    return m_length;
}
