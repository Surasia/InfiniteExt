#ifndef HAVOKSCRIPT_HPP
#define HAVOKSCRIPT_HPP
#include <cstdint>

struct Hks
{
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
    static uint64_t DoString(const char *string);
    /* Public Variables */
    struct CompilerSettings
    {
        uint64_t emitStructCode; // hksBool
        const char **stripNames;
        uint32_t emitMemoCode;          // hksBool
        uint32_t isMemoTestingMode;     // hksBool
        uint32_t bytecodeSharingFormat; // BytecodeSharingFormat (0 off, 1 on, 2 secure)
        uint32_t enableIntLiterals;     // IntLiteralsFormat (NONE, LUD, 32bit, UI64, 64bit, all)
        int unknown1;
        void *unknown2;
        int (*debugMap)(const char *filename, int lua_line);
    };

private:
    /* Function Type Definitions */
    using GetGlobal = int(__fastcall *)(uintptr_t state, char *string);
    static inline GetGlobal GetGlobalH = nullptr;
    static inline GetGlobal GetGlobalA = nullptr;
    using PCall = uint64_t(__fastcall *)(uintptr_t state, int function, uint32_t i, int u);
    static inline PCall PCallH = nullptr;
    static inline PCall PCallA = nullptr;
    using LoadBuffer = uint64_t(__fastcall *)(uintptr_t state, const struct Hks::CompilerSettings *settings, const char *buffer, uint64_t length, const char *unknown1);
    static inline LoadBuffer LoadBufferH = nullptr;
    static inline LoadBuffer LoadBufferA = nullptr;
    /* Private Functions */
    static int GetGlobalHook(uintptr_t state, char *string);
    static uint64_t PCallHook(uintptr_t state, int function, uint32_t i, int u);
    static uint64_t LoadBufferHook(uintptr_t state, const struct Hks::CompilerSettings *settings, const char *buffer, __int64 length, const char *unknown1);
    /* Private Variables */
    static inline uintptr_t LuaState = 0;
};

#endif
