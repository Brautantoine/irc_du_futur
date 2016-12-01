#ifndef PACKET_H_INCLUDED
#define PACKET_H_INCLUDED

class Packet {
public:
    Packet(std::string data);
    int getSize();
private:
    int m_size;
    std::string m_data;
};

#endif // PACKET_H_INCLUDED
