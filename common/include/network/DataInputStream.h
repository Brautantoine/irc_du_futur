#ifndef DATAINPUTSTREAM_H
#define DATAINPUTSTREAM_H

#include <winsock2.h>
#include <string>

class DataInputStream
{
    private:
        SOCKET m_socket;

    public:
        DataInputStream(SOCKET socket);
        ~DataInputStream();

        std::string readString();
        char *readBytes(int length);
        char readByte();
        short int readShort();
};

#endif
