#include "network/DataInputStream.h"
#include "exceptions/ClientDisconnectedException.h"
#include "exceptions/NothingToReceiveException.h"
#include <stdexcept>
#include <iostream>

DataInputStream::DataInputStream(SOCKET socket) : m_socket(socket) {
}

DataInputStream::~DataInputStream() {
}

std::string DataInputStream::readString() {
    unsigned short int string_length = readShort();

    char *msg_buffer = new char[string_length];
    int recvLength = recv(m_socket, msg_buffer, string_length, 0);

    if (recvLength < 0) {
        delete msg_buffer;
        throw NothingToReceiveException();
    }
    else if (recvLength == 0) {
        delete msg_buffer;
        throw ClientDisconnectedException();
    }

    std::string message(msg_buffer);

    delete msg_buffer;

    return message;
}

char *DataInputStream::readBytes(int length) {
    char *bytes = new char[length];

    int recvLength = recv(m_socket, bytes, length, 0);

    if (recvLength < 0) {
        delete bytes;
        throw NothingToReceiveException();
    }
    else if (recvLength == 0) {
        delete bytes;
        throw ClientDisconnectedException();
    }

    return bytes;
}

char DataInputStream::readByte() {
    char b;
    int recvLength = recv(m_socket, &b, 1, 0);

    if (recvLength < 0)
        throw NothingToReceiveException();
    else if (recvLength == 0)
        throw ClientDisconnectedException();

    return b;
}

short int DataInputStream::readShort() {
    char bytes[2];
    bytes[0] = readByte();
    bytes[1] = readByte();

    short int value = (bytes[0] << 8) | (bytes[1]);

    return value;
}
