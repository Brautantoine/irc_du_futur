#ifndef EVENTCLIENTDISCONNECT_H
#define EVENTCLIENTDISCONNECT_H

#include "events/Event.h"
#include "ServerClient.h"

class EventClientDisconnect : public Event
{
    public:
        EventClientDisconnect(Client *client);
        ~EventClientDisconnect();

        Client *getClient();

    private:
        Client *m_client;
};

#endif
