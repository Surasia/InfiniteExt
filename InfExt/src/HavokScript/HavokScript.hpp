#ifndef HAVOKSCRIPT_HPP
#define HAVOKSCRIPT_HPP
#include <cstdint>
#include <lua.hpp>

struct Hks {
public:
    /* Hooks */
    static void HookHavokScript(uintptr_t ModuleBase);

private:
    /* Function Type Definitions */
    using GetGlobal = int(__fastcall *)(lua_State *state, char *string);
    static GetGlobal GetGlobalH;
    static GetGlobal GetGlobalA;
    /* Private Functions */
    static int GetGlobalHook(lua_State *state, char *string);
};

#endif
