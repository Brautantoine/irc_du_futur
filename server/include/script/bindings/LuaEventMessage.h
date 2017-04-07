#ifndef LUAEVENTMESSAGE_H
#define LUAEVENTMESSAGE_H

extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}

namespace LuaBindings
{
    void EventMessage_register(lua_State *L);
}

#endif
