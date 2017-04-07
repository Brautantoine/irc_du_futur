#ifndef EVENTCLIENTCONNECT_H
#define EVENTCLIENTCONNECT_H

#include "events/Event.h"
#include "ServerClient.h"

class EventClientConnect : public Event
{
    public:
        EventClientConnect(Client *client);
        ~EventClientConnect();

        Client *getClient();

    private:
        Client *m_client;
};

#endif
