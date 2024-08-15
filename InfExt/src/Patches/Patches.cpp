#include "Patches.hpp"
#include "../Logger/Logger.hpp"
#include "../Globals.hpp"

void Patches::ToggleForgeHiddenCategories()
{
    Logger& logger = Logger::GetInstance(false);
    bool* boolPtr = reinterpret_cast<bool*>(GetModuleBase() + 0x50C3140);
    logger.Log(Logger::INFO, "Hide Forge Category set to: {}", *boolPtr ? "true" : "false");
    *boolPtr = !(*boolPtr); 
}

void Patches::ToggleHUD()
{
    Logger& logger = Logger::GetInstance(false);
    bool* boolPtr = reinterpret_cast<bool*>(GetModuleBase() + 0x482DCA0);
    logger.Log(Logger::INFO, "HUD set to: {}", *boolPtr ? "true" : "false");
    *boolPtr = !(*boolPtr);
}

void Patches::ToggleWatermark()
{
    Logger& logger = Logger::GetInstance(false);
    bool* boolPtr = reinterpret_cast<bool*>(GetModuleBase() + 0x489E160);
    logger.Log(Logger::INFO, "Watermark set to: {}", *boolPtr ? "true" : "false");
    *boolPtr = !(*boolPtr);
}

void Patches::ToggleKillVolumes()
{
    Logger& logger = Logger::GetInstance(false);
    bool* boolPtr = reinterpret_cast<bool*>(GetModuleBase() + 0x4ED5B34);
    logger.Log(Logger::INFO, "Kill Volume set to: {}", *boolPtr ? "true" : "false");
    *boolPtr = !(*boolPtr);
}
