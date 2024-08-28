#include "Patches.hpp"
#include "../Globals.hpp"
#include "../Logger/Logger.hpp"

void Patches::ToggleForgeHiddenCategories()
{
    Logger &logger = Logger::GetInstance(false);
    constexpr uintptr_t offset = 0x50C31C0;
    bool *boolPtr = reinterpret_cast<bool *>(GetModuleBase() + offset);
    logger.Log(Logger::INFO, "Hide Forge Category set to: {}", *boolPtr ? "true" : "false");
    *boolPtr = !(*boolPtr);
}

void Patches::ToggleHUD()
{
    Logger &logger = Logger::GetInstance(false);
    constexpr uintptr_t offset = 0x482DCE0;
    bool *boolPtr = reinterpret_cast<bool *>(GetModuleBase() + offset);
    logger.Log(Logger::INFO, "HUD set to: {}", *boolPtr ? "true" : "false");
    *boolPtr = !(*boolPtr);
}

void Patches::ToggleWatermark()
{
    Logger &logger = Logger::GetInstance(false);
    constexpr uintptr_t offset = 0x489E1A0;
    bool *boolPtr = reinterpret_cast<bool *>(GetModuleBase() + offset);
    logger.Log(Logger::INFO, "Watermark set to: {}", *boolPtr ? "true" : "false");
    *boolPtr = !(*boolPtr);
}

void Patches::ToggleKillVolumes()
{
    Logger &logger = Logger::GetInstance(false);
    constexpr uintptr_t offset = 0x4ED5BB4;
    bool *boolPtr = reinterpret_cast<bool *>(GetModuleBase() + offset);
    logger.Log(Logger::INFO, "Kill Volume set to: {}", *boolPtr ? "true" : "false");
    *boolPtr = !(*boolPtr);
}
