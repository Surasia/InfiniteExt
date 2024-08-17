#include "Memory.hpp"
#include "Logger/Logger.hpp"

UINT64 Memory::CheckCodeAccess(UINT64 startaddress)
{
    MEMORY_BASIC_INFORMATION mbi{};

    const auto *safeAdress = reinterpret_cast<LPCVOID>(startaddress);
    if (VirtualQuery(safeAdress, &mbi, sizeof(mbi)) != 0)
    {
        if (mbi.Protect != PAGE_NOACCESS && mbi.Protect == PAGE_EXECUTE_READ)
        {
            return 1;
        }
    }

    return 0;
}

DWORD Memory::HookFunction(LPVOID pTarget, LPVOID pDetour, LPVOID pTrampoline)
{
    Logger &logger = Logger::GetInstance(false);
    if (!isMHInit)
    {
        if (MH_Initialize() != MH_OK)
        {
            logger.Log(Logger::CRITICAL, "MHInit failed!");
            return 1;
        }
        logger.Log(Logger::INFO, "Hooks Initialized!");
        isMHInit = true;
    }
    if (MH_CreateHook(pTarget, pDetour, static_cast<LPVOID *>(pTrampoline)) != MH_OK)
    {
        logger.Log(Logger::CRITICAL, "MH_CreateHook failed!");
        return 1;
    }

    if (MH_EnableHook(pTarget) != MH_OK)
    {
        logger.Log(Logger::CRITICAL, "MH_EnableHook failed!");
        return 1;
    }

    return 0;
}

DWORD Memory::OnAccessHookFunction(PVOID pTarget, LPVOID pDetour, LPVOID pTrampoline)
{
    bool isWaiting = true;
    uintptr_t accessPointer = 0;
    Logger &logger = Logger::GetInstance(false);

    while (isWaiting)
    {
        accessPointer = Memory::CheckCodeAccess(reinterpret_cast<uintptr_t>(pTarget));

        if (accessPointer != 0)
        {
            Memory::HookFunction(pTarget, pDetour, pTrampoline);
        }
        else
        {
            logger.Log(Logger::CRITICAL, "Failed to hook code!");
        }

        isWaiting = false;
    }
    return 0;
}

void Memory::WriteBytes(uintptr_t pAddress, BYTE *pBytes, UINT szSize)
{
    DWORD oldProtect = 0;
    if (VirtualProtect(reinterpret_cast<LPVOID>(pAddress), szSize, PAGE_EXECUTE_READWRITE, &oldProtect) != 0)
    {
        memcpy(reinterpret_cast<LPVOID>(pAddress), pBytes, szSize);
        VirtualProtect(reinterpret_cast<LPVOID>(pAddress), szSize, oldProtect, &oldProtect);
    }
}
