#include "Forge.hpp"
#include "../Logger/Logger.hpp"


void Forge::ToggleForgeHiddenCategories()
{
    Logger& logger = Logger::GetInstance(false);
    uintptr_t moduleBase = reinterpret_cast<uintptr_t>(GetModuleHandleA("HaloInfinite.exe"));

    bool* boolPtr = reinterpret_cast<bool*>(moduleBase + 0x50C3140);
    logger.Log(Logger::INFO, "Hide Forge Category set to: {}", *boolPtr ? "true" : "false");
    *boolPtr = !(*boolPtr); 
}
