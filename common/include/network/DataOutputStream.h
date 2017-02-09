#ifndef DATAOUTPUTSTREAM_H
#define DATAOUTPUTSTREAM_H

#include <winsock2.h>
#include <string>

class DataOutputStream
{
    private:
        SOCKET m_socket;

    public:
        DataOutputStream(SOCKET m_socket);
        ~DataOutputStream();

        void writeByte(char value);
        void writeBytes(const char *bytes, int length);
        void writeShort(short int value);
        void writeString(std::string message);
};

#endif
