#include "Patches.hpp"
#include "../Globals.hpp"
#include "../Logger/Logger.hpp"

// Forge_DisableForgeHiddenCategory
void Patches::ToggleForgeHiddenCategories()
{
    Logger &logger = Logger::GetInstance(false);
    constexpr uintptr_t offset = 0x50E1840;
    bool *boolPtr = reinterpret_cast<bool *>(GetModuleBase() + offset);
    logger.Log(Logger::INFO, "Hide Forge Category set to: {}", *boolPtr ? "true" : "false");
    *boolPtr = !(*boolPtr);
}

// hud_disable
void Patches::ToggleHUD()
{
    Logger &logger = Logger::GetInstance(false);
    constexpr uintptr_t offset = 0x484B060;
    bool *boolPtr = reinterpret_cast<bool *>(GetModuleBase() + offset);
    logger.Log(Logger::INFO, "HUD set to: {}", *boolPtr ? "true" : "false");
    *boolPtr = !(*boolPtr);
}

// force_watermark_on
void Patches::ToggleWatermark()
{
    Logger &logger = Logger::GetInstance(false);
    constexpr uintptr_t offset = 0x48BB520;
    bool *boolPtr = reinterpret_cast<bool *>(GetModuleBase() + offset);
    logger.Log(Logger::INFO, "Watermark set to: {}", *boolPtr ? "true" : "false");
    *boolPtr = !(*boolPtr);
}

// kill_volumes_disable
void Patches::ToggleKillVolumes()
{
    Logger &logger = Logger::GetInstance(false);
    constexpr uintptr_t offset = 0x4EF3434;
    bool *boolPtr = reinterpret_cast<bool *>(GetModuleBase() + offset);
    logger.Log(Logger::INFO, "Kill Volume set to: {}", *boolPtr ? "true" : "false");
    *boolPtr = !(*boolPtr);
}
