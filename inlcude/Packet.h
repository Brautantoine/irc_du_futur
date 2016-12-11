#ifndef PACKET_H
#define PACKET_H

#define PACKET_SIZE 512

class Packet {
private:
    char *m_buffer;
    int m_length;
public:
    Packet(char *buffer);
    ~Packet();

    char *getBuffer();
    int getLength();
};

#endif // PACKET_H
