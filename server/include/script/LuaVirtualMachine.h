#ifndef LUAVIRTUALMACHINE_H
#define LUAVIRTUALMACHINE_H

extern "C" {
    #include <lua.h>
    #include <lauxlib.h>
    #include <lualib.h>
}

class LuaVirtualMachine {
    public:
        LuaVirtualMachine();
        ~LuaVirtualMachine();

        lua_State *luaState;
};

#endif
