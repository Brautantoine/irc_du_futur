#ifndef PACKET_H
#define PACKET_H

#include <string>
#define PACKET_SIZE 512

class Packet {
private:
    std::string m_buffer;
public:
    Packet(char *buffer);

    std::string getBuffer();
};

#endif // PACKET_H
