#ifndef HAVOKSCRIPT_HPP
#define HAVOKSCRIPT_HPP
#include <cstdint>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <sstream>

struct Hks {
public:
	/* Operators */
	Hks() = default;
    Hks(const Hks &) = default;
    Hks(Hks &&) = delete;
    Hks &operator=(const Hks &) = default;
    Hks &operator=(Hks &&) = delete;
    ~Hks() = default;
    /* Hooks */
	static void HookHavokScript(uintptr_t ModuleBase);
	static uint64_t DoFile(const char* filename);
	static uint64_t DoString(const char* string);

private:
	/* Function Type Definitions */
	using GetGlobal = int(__fastcall*)(uintptr_t state, char* string);
	static inline GetGlobal GetGlobalH = nullptr;
	static inline GetGlobal GetGlobalA = nullptr;

	using PCall = uint64_t(__fastcall*)(uintptr_t state, int function, uint32_t i, int u);
	static inline PCall PCallH = nullptr;
	static inline PCall PCallA = nullptr;

	using LoadBuffer = uint64_t(__fastcall*)(uintptr_t state, const struct HksCompilerSettings* compilerSettings, const char* buffer, __int64 length, const char* unknown1);
	static inline LoadBuffer LoadBufferH = nullptr;
	static inline LoadBuffer LoadBufferA = nullptr;

	/* Private Functions */
	static int GetGlobalHook(uintptr_t state, char* string);
	static inline uint64_t PCallHook(uintptr_t state, int function, uint32_t i, int u);
	static inline uint64_t LoadBufferHook(uintptr_t state, const struct HksCompilerSettings* compilerSettings, const char* buffer, __int64 length, const char* unknown1);

	/* Private Variables */
	static inline uintptr_t LuaState = 0;
};

#endif
