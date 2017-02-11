#ifndef GLOBALS_H
#define GLOBALS_H

#include "ConfigurationServer.h"
#include "Server.h"

namespace Globals {
    extern Server *server;
    extern ConfigurationServer *cfg;

    extern const unsigned short int PROTOCOL_VERSION;
}

#endif
