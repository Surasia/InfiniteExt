#include "HavokScript.hpp"
#include "../Memory.hpp"

/* Declare private variables. */
Hks::GetGlobal Hks::GetGlobalH = nullptr;
Hks::GetGlobal Hks::GetGlobalA = nullptr;

int Hks::GetGlobalHook(lua_State *state, char *string)
{
    return GetGlobalA(state, string);
}


void Hks::HookHavokScript(uintptr_t ModuleBase)
{
    const uintptr_t GetGlobalOffset = 0x80CB4C;
    GetGlobalH = hook_function<GetGlobal>(ModuleBase, GetGlobalOffset, &GetGlobalHook, &GetGlobalA);
}
