#include "script/bindings/LuaEventMessage.h"
#include "events/EventMessage.h"

static EventMessage *l_CheckEventMessage(lua_State * L, int n) {
    return *(EventMessage **)luaL_checkudata(L, n, "EventMessage");
}

static int l_EventMessage_getClient(lua_State *L) {
    EventMessage *c = l_CheckEventMessage(L, 1);

    Client **boxedPointer = (Client**)lua_newuserdata(L, sizeof(Client*));
    *boxedPointer = c->getClient();

    luaL_getmetatable(L, "Client");
    lua_setmetatable(L, -2);

    return 1;
}

static int l_EventMessage_getMessage(lua_State *L) {
    EventMessage *c = l_CheckEventMessage(L, 1);

    lua_pushstring(L, c->getMessage().c_str());

    return 1;
}

static int l_EventMessage_setMessage(lua_State *L) {
    EventMessage *c = l_CheckEventMessage(L, 1);

    const char *message = luaL_checkstring(L, 2);
    c->setMessage(std::string(message));

    return 1;
}

static int l_EventMessage_free(lua_State * L) {
    EventMessage *c = l_CheckEventMessage(L, 2);
    delete c;

    return 0;
}

namespace LuaBindings
{
    void EventMessage_register(lua_State *L)
    {
        luaL_Reg gEventMessageFuncs[] = {
            {"getClient", l_EventMessage_getClient},
            {"getMessage", l_EventMessage_getMessage},
            {"setMessage", l_EventMessage_setMessage},
            { "__gc", l_EventMessage_free},
            {NULL, NULL}
        };

        luaL_newmetatable(L, "EventMessage");
        luaL_setfuncs(L, gEventMessageFuncs, 0);
        lua_pushvalue(L, -1);
        lua_setfield(L, -1, "__index");
        lua_setglobal(L, "EventMessage");
    }
}
