#include "script/Script.h"
#include <iostream>
#include <stdlib.h>
#include "Globals.h"

Script::Script(std::string filename) : m_filename(filename) {
    std::string path("scripts/");
    path += m_filename;
    path += ".lua";

    lua_State *L = Globals::luaVM->luaState;

    luaL_loadfile(L, path.c_str());

    lua_newtable(L); //Create _ENV tables
    lua_newtable(L); //Create metatable
    lua_getglobal(L, "_G"); //Get the global table
    lua_setfield(L, -2, "__index");
    lua_setmetatable(L, -2); //Set global as the metatable
    lua_setfield(L, LUA_REGISTRYINDEX, m_filename.c_str()); //Push to registry with a unique name.
    lua_getfield(L, LUA_REGISTRYINDEX, m_filename.c_str()); //Retrieve it.
    lua_setupvalue(L, 1, 1); //Set the upvalue (_ENV)
    lua_pcall(L, 0, LUA_MULTRET, 0); //Run chunks
}

Script::~Script()
{
}

void Script::onEnable() {
    lua_State *L = Globals::luaVM->luaState;

    lua_getfield(L, LUA_REGISTRYINDEX, m_filename.c_str());
    lua_getfield(L, -1, "onEnable");

    if (!lua_isfunction(L, -1)) {
        std::cerr << "onEnable is not a function in " << m_filename << std::endl;
        return;
    }

    if (lua_pcall(L, 0, 0, 0) != 0) { // do the call (0 arguments, 0 result)
        std::cerr << "error running onEnable function: " << lua_tostring(L, -1) << " in " << m_filename << std::endl;
    }
}

void Script::onDisable() {
    lua_State *L = Globals::luaVM->luaState;

    lua_getfield(L, LUA_REGISTRYINDEX, m_filename.c_str());
    lua_getfield(L, -1, "onDisable");

    if (!lua_isfunction(L, -1)) {
        std::cerr << "onDisable is not a function in " << m_filename << std::endl;
        return;
    }

    if (lua_pcall(L, 0, 0, 0) != 0) { // do the call (0 arguments, 0 result)
        std::cerr << "error running onDisable function: " << lua_tostring(L, -1) << " in " << m_filename << std::endl;
    }
}

bool Script::onMessage(EventMessage *event) {
    lua_State *L = Globals::luaVM->luaState;

    lua_getfield(L, LUA_REGISTRYINDEX, m_filename.c_str());
    lua_getfield(L, -1, "onMessage");

    if (!lua_isfunction(L, -1)) {
        std::cerr << "onMessage is not a function in " << m_filename << std::endl;
        return false;
    }

    EventMessage **boxedPointer = (EventMessage**)lua_newuserdata(L, sizeof(EventMessage*));
    *boxedPointer = event;
    luaL_getmetatable(L, "EventMessage");
    lua_setmetatable(L, -2);

    if (lua_pcall(L, 1, 1, 0) != 0) { // do the call (1 arguments, 1 result)
        std::cerr << "error running function: " << lua_tostring(L, -1) << std::endl;
    }

    if (!lua_isboolean(L, -1)) {
        std::cerr << "function onMessage must return a bool" << std::cerr;
    }

    bool value = lua_toboolean(L, -1);
    lua_pop(L, 1);  // pop returned value

    return value;
}
