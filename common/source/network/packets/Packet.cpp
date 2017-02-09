#include "network/packets/Packet.h"
#include <cstring> //for memcpy
#include <iostream>

Packet::Packet(int id) : m_id(id), m_payload(nullptr) {
}

Packet::~Packet() {
    delete m_payload;
}

int Packet::getId() {
    return m_id;
}

char *Packet::getPayload() {
    return m_payload;
}

char *Packet::getBytes(const std::string &str) {
    //TODO CHECK IF STR SIZE < 65535 or throw error

    char *bytes_short = getBytes(str.size()+1);
    char *bytes = new char[2 + str.size() + 1];
    std::memcpy(bytes, bytes_short, 2);
    std::memcpy(bytes+2, str.c_str(), str.size()+1);

    delete bytes_short;
    return bytes;
}

char *Packet::getBytes(const short int value) {
    char *bytes = new char[2];

    char msb = (char)((value & 0xF0) >> 4);
    char lsb = (char)(value & 0x0F);

    bytes[0] = msb;
    bytes[1] = lsb;

    return bytes;
}
