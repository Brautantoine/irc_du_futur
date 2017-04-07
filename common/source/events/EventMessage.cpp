#include "events/EventMessage.h"

EventMessage::EventMessage(Client *client, std::string message) : m_client(client), m_message(message) {
}

EventMessage::~EventMessage() {
}

Client *EventMessage::getClient() {
    return m_client;
}

std::string EventMessage::getMessage() {
    return m_message;
}

void EventMessage::setMessage(std::string message) {
    m_message = message;
}
