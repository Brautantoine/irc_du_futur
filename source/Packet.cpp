#include "Server.h"

Packet::Packet(std::string data) : m_data(data), m_size(m_data.size()) {
}

int Packet::getSize() {
    return m_size;
}
