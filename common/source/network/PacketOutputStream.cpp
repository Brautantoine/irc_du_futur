#include "network/PacketOutputStream.h"

PacketOutputStream::PacketOutputStream(DataOutputStream dos) : m_dataOutputStream(dos) {
}

PacketOutputStream::~PacketOutputStream() {
}

void PacketOutputStream::writePacket(Packet *packet) {
    m_dataOutputStream.writeBytes(packet->getPayload(), packet->getLength());
}
