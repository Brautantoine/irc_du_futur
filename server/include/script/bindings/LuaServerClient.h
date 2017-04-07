#ifndef LUASERVERCLIENT_H
#define LUASERVERCLIENT_H

extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}

namespace LuaBindings
{
    void Client_register(lua_State *L);
}

#endif
