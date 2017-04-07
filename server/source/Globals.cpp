#include "Globals.h"

namespace Globals {
    Server *server = nullptr;
    ConfigurationServer *cfg = nullptr;

    const unsigned short int PROTOCOL_VERSION = 0x1;

    LuaVirtualMachine *luaVM = nullptr;
    ScriptManager *scriptManager = nullptr;
}
