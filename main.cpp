#include <iostream>

extern "C"
{
    #include "lua.h"
    #include "lauxlib.h"
    #include "lualib.h"
}


int main()
{

    const char* cmd = "a = 7 + 11";

    // L is a standard lua virtual machine
    lua_State* L = luaL_newstate();

    // Tell lua do execute this string
    int r = luaL_dostring(L, cmd);

    if (r == LUA_OK)
    {
        // Try to get value of a
        lua_getglobal(L, "a");
        if (lua_isnumber(L, -1))
        {
            std::cout << "a = " << lua_tonumber(L, -1) << std::endl;
        }
    }
    else
    {
        // If code execution fails ->
        // grab error from lua stack and cout
        std::string errormsg = lua_tostring(L, -1);
        std::cout << errormsg << std::endl;
    }

    system("pause");
    lua_close(L);
    return 0;
}