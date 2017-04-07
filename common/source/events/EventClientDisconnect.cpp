#include "events/EventClientDisconnect.h"

EventClientDisconnect::EventClientDisconnect(Client *client) : m_client(client) {
}

EventClientDisconnect::~EventClientDisconnect() {
}

Client *EventClientDisconnect::getClient() {
    return m_client;
}
