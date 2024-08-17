#include "Client.hpp"
#include "./HavokScript/HavokScript.hpp"
#include "./Logger/Logger.hpp"
#include "./Misc/ChromaSDK.hpp"
#include "./UniversalHook/hooks/hooks.hpp"
#include "Exports.hpp"
#include "Globals.hpp"


static DWORD WINAPI CreateConsole()
{
    FILE *dummy = nullptr;
    AllocConsole();
    AttachConsole(GetCurrentProcessId());
    {
        std::lock_guard<std::mutex> lock(consoleMutex);
        if (freopen_s(&dummy, "CONIN$", "r", stdin) != 0 || freopen_s(&dummy, "CONOUT$", "w", stdout) != 0 ||
            freopen_s(&dummy, "CONOUT$", "w", stderr) != 0)
        {
            std::cerr << "Failed to redirect console streams !\n";
            return 1;
        }
    }
    Logger &logger = Logger::GetInstance(false);
    logger.Log(Logger::INFO, "Console Initialized!");
    return 0;
}

static DWORD WINAPI DestroyConsole()
{
    Logger &logger = Logger::GetInstance(false);
    logger.Log(Logger::INFO, "Destroying Console...");
    if (FreeConsole() == 0)
    {
        logger.Log(Logger::_ERROR, "Console failed to close!");
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

static DWORD WINAPI DestroyHook()
{
    Logger &logger = Logger::GetInstance(false);
    stopThread = true;
    cv.notify_all();

    MH_DisableHook(MH_ALL_HOOKS);
    MH_Uninitialize();

    if (hMutex)
    {
        ReleaseMutex(hMutex);
        CloseHandle(hMutex);
        hMutex = NULL;
    }

    logger.Log(Logger::INFO, "Hook Destroyed!");
    return 0;
}

static DWORD SetupHook()
{
    Logger &logger = Logger::GetInstance(false);

    constexpr LPCSTR moduleName = "HaloInfinite.exe";
    ModuleBase = reinterpret_cast<uintptr_t>(GetModuleHandleA(moduleName));
    if (ModuleBase == 0)
    {
        logger.Log(Logger::CRITICAL, "Failed to get module handle!");
        return 1;
    }

    ChromaSDK::HookChroma(ModuleBase);
    Hks::HookHavokScript(ModuleBase);
    return 0;
}

static DWORD WINAPI MainThread(LPVOID lpParameter)
{
    Logger &logger = Logger::GetInstance(false);
    CreateConsole();
    SetupHook();
    Hooks::Init();
    logger.Log(Logger::INFO, "ImGui Initialized!");
    return 0;
}

DWORD WINAPI OnProcessDetach(LPVOID lpParam);

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
    if (fdwReason == DLL_PROCESS_ATTACH)
    {
        DisableThreadLibraryCalls(hinstDLL);
        hMutex = CreateMutexA(NULL, TRUE, "UniqueDLLInstanceMutex");
        if (hMutex == nullptr || GetLastError() == ERROR_ALREADY_EXISTS)
        {
            if (hMutex != nullptr)
            {
                CloseHandle(hMutex);
                hMutex = nullptr;
            }
            return FALSE;
        }

        HANDLE hHandle = CreateThread(nullptr, 0, MainThread, hinstDLL, 0, NULL);
        if (hHandle != nullptr)
        {
            CloseHandle(hHandle);
        }
    }
    else if (fdwReason == DLL_PROCESS_DETACH && (lpReserved == nullptr))
    {
        OnProcessDetach(nullptr);
    }

    return TRUE;
}

DWORD WINAPI OnProcessDetach(LPVOID lpParam)
{
    DestroyHook();
    DestroyConsole();
    Hooks::Free();
    MH_Uninitialize();
    return 0;
}
