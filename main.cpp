#include <iostream>
#include <fstream>
#include <sstream>

extern "C"
{
    #include "lua.h"
    #include "lauxlib.h"
    #include "lualib.h"
}


int main()
{

    std::ifstream filein("script.lua");
    std::stringstream buffer;
    buffer << filein.rdbuf(); 
    filein.close();

    // L is a standard lua virtual machine
    lua_State* L = luaL_newstate();

    // Tell lua do execute this string
    int r = luaL_dostring(L, buffer.str().c_str());

    if (r == LUA_OK)
    {
        // Try to get value of c
        lua_getglobal(L, "c");
        if (lua_isnumber(L, -1))
        {
            std::cout << "c = " << lua_tonumber(L, -1) << std::endl;
        }
    }
    else
    {
        // If code execution fails ->
        // grab error from lua stack and cout
        std::string errormsg = lua_tostring(L, -1);
        std::cout << errormsg << std::endl;
    }

    lua_close(L);
    return 0;
}