#include "HavokScript.hpp"
#include "../Memory.hpp"
#include <stdio.h>
#include "../Logger/Logger.hpp"
#include "../UniversalHook/Menu/Toggles.hpp"

int Hks::GetGlobalHook(uintptr_t state, char *string)
{
    LuaState = state;
    return GetGlobalA(state, string);
}

uint64_t Hks::PCallHook(uintptr_t state, int function, uint32_t i, int u)
{
    uint64_t result = PCallA(state, function, i, u);
    return result;
}

uint64_t Hks::LoadBufferHook(uintptr_t state, const struct Hks::CompilerSettings *settings, const char *buffer, __int64 length, const char *unknown1)
{
    uint64_t result = LoadBufferA(state, settings, buffer, length, unknown1);
    return result;
}


uint64_t Hks::DoString(const char *string)
{
    size_t stringLength = strlen(string);

    if (LoadBufferA(LuaState, (const struct CompilerSettings *)(*((uintptr_t *)LuaState + 2) + 1368), string, stringLength, string) != 0)
    {
        return 1;
    }

    uint64_t call_result = PCallA(LuaState, 0, -1, 0);
    if (call_result != 0)
    {
        return 1;
    }
    return call_result;
}

int Hks::LuaPrintHook(char *Buffer, size_t BufferCount, char *Format, va_list ArgList)
{

    int result;           // eax

    result = __stdio_common_vsnprintf_s(0x24, Buffer, BufferCount, BufferCount - 1, Format, 0LL, ArgList);
    Logger &logger = Logger::GetInstance(false);
    if (printsEnabled)
    {
        logger.Log(Logger::INFO, "{}", Buffer);
    }
    logger.Log(Logger::INFO, "{}", Buffer);
    Buffer[BufferCount - 1] = 0;
    if (result < 0)
        return -1;
    return result;
}


void Hks::HookHavokScript(uintptr_t ModuleBase)
{
    // Search for "_OBJECT_META", follow the ref, and find this function directly below.
    const uintptr_t GetGlobalOffset = 0x78A57C;
    GetGlobalH = hook_function<GetGlobal>(ModuleBase, GetGlobalOffset, &GetGlobalHook, &GetGlobalA);
    // Search for "GetDescription",and you'll find it below in the second if block.
    const uintptr_t PCallOffset = 0x6C939C;
    PCallH = hook_function<PCall>(ModuleBase, PCallOffset, &PCallHook, &PCallA);
    // Search for "loadstring", follow the second ref, and check the function inside the if block.
    const uintptr_t LoadBufferOffset = 0xA4AEE0;
    LoadBufferH = hook_function<LoadBuffer>(ModuleBase, LoadBufferOffset, &LoadBufferHook, &LoadBufferA);
    const uintptr_t LuaPrintOffset = 0x54BF60;
    LuaPrintH = hook_function<LuaPrint>(ModuleBase, LuaPrintOffset, &LuaPrintHook, &LuaPrintA);
}
