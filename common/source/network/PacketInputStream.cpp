#include "network/PacketInputStream.h"
#include "network/packets/Packet0ClientIdentification.h"
#include "network/packets/Packet1Ping.h"
#include "network/packets/Packet2Message.h"
#include "exceptions/NothingToReceiveException.h"
#include <iostream>
#include <stdexcept>

PacketInputStream::PacketInputStream(DataInputStream dataInputStream) : m_dataInputStream(dataInputStream), m_currentId(-1) {
}

PacketInputStream::~PacketInputStream() {
}

Packet *PacketInputStream::nextPacket() {
    if (m_currentId == -1 || m_currentId > 2)
        throw std::length_error("Invalid packetID");

    Packet *p = nullptr;
    switch (m_currentId) {
        case 0x0:
            p = new Packet0ClientIdentification(&m_dataInputStream);
            break;
        case 0x1:
            p = new Packet1Ping();
            break;
        case 0x2:
            p = new Packet2Message(&m_dataInputStream);
            break;
    }

    m_currentId = -1;
    return p;
}

bool PacketInputStream::hasPacket() {
    char packetId = -1;
    try {
        packetId = m_dataInputStream.readByte();
    }
    catch (const NothingToReceiveException &e) {
        return false;
    }

    if (packetId >= 0) {
        m_currentId = packetId;
        return true;
    }

    return false;
}
