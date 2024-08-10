#include "Client.hpp"
#include "Exports.hpp"
#include "./HavokScript/HavokScript.hpp"
#include "./Lua/LuaHook.hpp"
#include "./Misc/ChromaSDK.hpp"
#include "./Variant/Variant.hpp"

std::mutex consoleMutex;
std::condition_variable cv;
std::atomic<bool> stopThread(false);
std::thread mainThread;

DWORD WINAPI CreateConsole()
{
    FILE *dummy = nullptr;
    AllocConsole();
    AttachConsole(GetCurrentProcessId());
    {
        std::lock_guard<std::mutex> lock(consoleMutex);
        if (freopen_s(&dummy, "CONIN$", "r", stdin) != 0 || freopen_s(&dummy, "CONOUT$", "w", stdout) != 0 ||
            freopen_s(&dummy, "CONOUT$", "w", stderr) != 0) {
            std::cerr << "Failed to redirect console streams !" << std::endl;
            return 1;
        }
    }
    return 0;
}

DWORD WINAPI DestroyConsole()
{
    if (FreeConsole() == 0) {
        std::cerr << "Console failed to close!" << std::endl;
    }

    {
        std::lock_guard<std::mutex> lock(consoleMutex);
        freopen_s(reinterpret_cast<FILE **>(stdin), "NUL:", "r", stdin);
        freopen_s(reinterpret_cast<FILE **>(stdout), "NUL:", "r", stdout);
        freopen_s(reinterpret_cast<FILE **>(stderr), "NUL:", "r", stderr);
    }

    std::cin.clear();
    std::cout.clear();
    std::cerr.clear();
    return 0;
}

DWORD WINAPI DestroyHook()
{
    stopThread = true;
    cv.notify_all();

    if (mainThread.joinable()) {
        mainThread.join();
    }

    MH_DisableHook(MH_ALL_HOOKS);
    MH_Uninitialize();
    return 0;
}

void ProcessCommands()
{
    while (!stopThread) {
        LuaVM::ProcessCommand();
    }
}


static DWORD SetupHook()
{
    uintptr_t ModuleBase = 0;

    LPCSTR moduleName = "HaloInfinite.exe";
    ModuleBase = reinterpret_cast<uintptr_t>(GetModuleHandleA(moduleName));
    if (ModuleBase == 0) {
        std::cerr << "Failed to get module handle for " << moduleName << std::endl;
        return 1;
    }

    ChromaSDK::HookChroma(ModuleBase);
    Hks::HookHavokScript(ModuleBase);
    Variant::HookVariant(ModuleBase);

    LuaVM::InitializeLua();
    LuaVM::HookVariantFunctions();
    mainThread = std::thread(ProcessCommands);
    return 0;
}


DWORD WINAPI MainThread(LPVOID lpParameter)
{
    SetupHook();
    return 0;
}


BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
    switch (dwReason) {
    case DLL_PROCESS_ATTACH:
        CreateConsole();
        DisableThreadLibraryCalls(hModule);
        CreateThread(nullptr, 0, MainThread, nullptr, 0, nullptr);
        break;
    case DLL_PROCESS_DETACH:
        DestroyHook();
        LuaVM::CleanLua();
        DestroyConsole();
        FreeLibraryAndExitThread(hModule, TRUE);
        break;
    default:
        break;
    }
    return TRUE;
}
