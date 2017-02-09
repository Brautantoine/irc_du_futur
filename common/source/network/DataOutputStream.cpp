#include "network/DataOutputStream.h"
#include "exceptions/ClientDisconnectedException.h"
#include <iostream>
#include <stdexcept>

DataOutputStream::DataOutputStream(SOCKET socket) : m_socket(socket) {
}

DataOutputStream::~DataOutputStream() {
}

void DataOutputStream::writeByte(char value) {
    int bytesSent = send(m_socket, &value, 1, 0);

    if (bytesSent < 0)
        std::cout << "writeByte: " << bytesSent << std::endl;
    else if (bytesSent == 0)
        throw ClientDisconnectedException();
}

void DataOutputStream::writeBytes(const char *bytes, int length) {
    int bytesSent = send(m_socket, bytes, length, 0);

    if (bytesSent < 0)
        std::cout << "writeBytes: " << bytesSent << std::endl;
    else if (bytesSent == 0)
        throw ClientDisconnectedException();
}

void DataOutputStream::writeShort(short int value) {
    char msb = (char)((value & 0xFF00) >> 4);
    char lsb = (char)(value & 0xFF);

    std::cout << "writeShort msb:" << msb << "lsb:" << lsb << std::endl;

    writeByte(msb);
    writeByte(lsb);
}

void DataOutputStream::writeString(std::string message) {
    if (message.size() > 65535)
        throw std::range_error("max string length: 65535");

    writeShort(message.size()+1);
    writeBytes(message.c_str(), message.size()+1);
}
