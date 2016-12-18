#ifndef PACKET_H
#define PACKET_H

#define PACKET_SIZE 512

class Packet {
private:
    const char *m_buffer;
    const int m_length;
public:
    Packet(char *buffer);
    ~Packet();

    const char *getBuffer();
    const int getLength();
};

#endif // PACKET_H
