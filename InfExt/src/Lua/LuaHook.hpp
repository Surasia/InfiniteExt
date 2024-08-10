#ifndef LUAHOOK_HPP
#define LUAHOOK_HPP
#include <sol/sol.hpp>
#include <string>

struct LuaVM {
public:
    static void HookVariantFunctions();
    static void InitializeLua();
    static void CleanLua();
    static void ProcessCommand();

private:
    static sol::state lua;
};

#endif
