#include "script/LuaVirtualMachine.h"
#include "script/bindings/LuaServerClient.h"
#include "script/bindings/LuaEventMessage.h"

LuaVirtualMachine::LuaVirtualMachine() : luaState(nullptr) {
    luaState = luaL_newstate();
    luaL_openlibs(luaState);

    LuaBindings::Client_register(luaState);
    LuaBindings::EventMessage_register(luaState);
}

LuaVirtualMachine::~LuaVirtualMachine() {
    lua_close(luaState);
}
