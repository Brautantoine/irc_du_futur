#include "events/EventClientConnect.h"

EventClientConnect::EventClientConnect(Client *client) : m_client(client) {
}

EventClientConnect::~EventClientConnect() {
}

Client *EventClientConnect::getClient() {
    return m_client;
}
