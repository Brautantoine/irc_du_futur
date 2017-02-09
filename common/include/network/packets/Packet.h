#ifndef PACKET_H
#define PACKET_H

#include <string>

class Packet {
    private:
        int m_id;
    protected:
        char *m_payload;

        char *getBytes(const std::string &str);
        char *getBytes(const short int value);
    public:
        Packet(int id);
        virtual ~Packet();

        int getId();
        char *getPayload();
        virtual unsigned int getLength() = 0; //Pure virtual
};

#endif
