#ifndef GLOBALS_H
#define GLOBALS_H

#include "script/LuaVirtualMachine.h"
#include "script/ScriptManager.h"
#include "ConfigurationServer.h"
#include "Server.h"

namespace Globals {
    extern Server *server;
    extern ConfigurationServer *cfg;

    extern const unsigned short int PROTOCOL_VERSION;

    extern LuaVirtualMachine *luaVM;
    extern ScriptManager *scriptManager;
}

#endif
