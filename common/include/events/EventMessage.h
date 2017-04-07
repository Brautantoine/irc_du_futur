#ifndef EVENTMESSAGE_H
#define EVENTMESSAGE_H

#include <string>
#include "events/Event.h"
#include "ServerClient.h"

class EventMessage : public Event
{
public:
    EventMessage(Client *client, std::string message);
    ~EventMessage();

    Client *getClient();

    std::string getMessage();
    void setMessage(std::string message);

private:
    Client *m_client;
    std::string m_message;
};

#endif
