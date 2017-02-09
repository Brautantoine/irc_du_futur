#include "exceptions/ClientDisconnectedException.h"

const char* ClientDisconnectedException::what() const throw() {
    return "Client Disconnected";
}
