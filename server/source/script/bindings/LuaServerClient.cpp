#include "script/bindings/LuaServerClient.h"
#include "ServerClient.h"

static Client *l_CheckClient(lua_State * L, int n)
{
    return *(Client **)luaL_checkudata(L, n, "Client");
}

static int l_Client_getUsername(lua_State *L)
{
    Client *c = l_CheckClient(L, 1);

    lua_pushstring(L, c->getUsername().c_str());

    return 1;
}

static int l_Client_getInetAdress(lua_State *L)
{
    Client *c = l_CheckClient(L, 1);

    lua_pushstring(L, c->getInetAdress());

    return 1;
}

static int l_Client_free(lua_State * L)
{
    Client *c = l_CheckClient(L, 1);
    delete c;

    return 0;
}
namespace LuaBindings
{
    void Client_register(lua_State *L)
    {
        luaL_Reg gClientFuncs[] =
        {
            {"getUsername", l_Client_getUsername},
            {"getInetAdress", l_Client_getInetAdress},
            { "__gc", l_Client_free},
            {NULL, NULL}
        };

        luaL_newmetatable(L, "Client");
        luaL_setfuncs(L, gClientFuncs, 0);
        lua_pushvalue(L, -1);
        lua_setfield(L, -1, "__index");
        lua_setglobal(L, "Client");
    }
}
