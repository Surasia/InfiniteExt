#ifndef LUAHOOK_HPP
#define LUAHOOK_HPP
#include <iostream>
#include <string>

struct LuaVM {
public:
	/* Operators */
	LuaVM() = default;
    LuaVM(const LuaVM &) = default;
    LuaVM(LuaVM &&) = delete;
    LuaVM &operator=(const LuaVM &) = default;
    LuaVM &operator=(LuaVM &&) = delete;
    ~LuaVM() = default;
    /* Public Functions */
	static void ProcessCommand();
};

#endif
