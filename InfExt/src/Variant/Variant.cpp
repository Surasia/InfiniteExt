#include "Variant.hpp"
#include "../Memory.hpp"


/* Declare private variables. */
Variant::GetVariant Variant::GetVariantH = nullptr;
Variant::GetVariant Variant::GetVariantA = nullptr;

uintptr_t Variant::GetVariantHook()
{
    uintptr_t result = GetVariantA();
    return result;
}

const char *Variant::GetEngineName()
{
    return reinterpret_cast<const char *>(GetVariantHook() + 28);
}

const char *Variant::GetVariantName()
{
    return reinterpret_cast<const char *>(GetVariantHook() + 156);
}

bool Variant::GetTeamsEnabled()
{
    uintptr_t address = GetVariantHook() + 4252;
    return *reinterpret_cast<bool *>(address);
}

bool Variant::GetTeamScoringEnabled()
{
    auto *pVariant = (uint8_t *)GetVariantHook();
    bool result = static_cast<bool>(pVariant[4252]);
    if (!result) {
        return false;
    }
    if (pVariant[4254] != 0U) {
        return static_cast<bool>(pVariant[4253]);
    }
    return result;
}

bool Variant::GetRequisitionEnabled()
{
    uintptr_t address = GetVariantHook() + 540;
    return *reinterpret_cast<bool *>(address);
}

bool Variant::GetReqVehiclesEnabled()
{
    uintptr_t address = GetVariantHook() + 545;
    return *reinterpret_cast<bool *>(address);
}

bool Variant::GetReqConsumableWeaponsEnabled()
{
    uintptr_t address = GetVariantHook() + 546;
    return *reinterpret_cast<bool *>(address);
}

bool Variant::GetReqLoadoutWeaponsEnabled()
{
    uintptr_t address = GetVariantHook() + 547;
    return *reinterpret_cast<bool *>(address);
}

bool Variant::GetReqArmorModsEnabled()
{
    uintptr_t address = GetVariantHook() + 547;
    return *reinterpret_cast<bool *>(address);
}

bool Variant::GetActiveSpartanTrackingEnabled()
{
    uintptr_t address = GetVariantHook() + 929435;
    return *reinterpret_cast<bool *>(address);
}

bool Variant::GetPassiveSpartanTrackingEnabled()
{
    uintptr_t address = GetVariantHook() + 929436;
    return *reinterpret_cast<bool *>(address);
}

bool Variant::GetREQVehicleCapPerMapEnabled()
{
    uintptr_t address = GetVariantHook() + 541;
    return *reinterpret_cast<bool *>(address);
}

int8_t Variant::GetREQVehicleCapPerMap()
{
    uintptr_t address = GetVariantHook() + 542;
    return *reinterpret_cast<int8_t *>(address);
}

bool Variant::GetREQVehicleCapPerTeamEnabled()
{
    uintptr_t address = GetVariantHook() + 543;
    return *reinterpret_cast<bool *>(address);
}

int8_t Variant::GetREQVehicleCapPerTeam()
{
    uintptr_t address = GetVariantHook() + 544;
    return *reinterpret_cast<int8_t *>(address);
}

int8_t Variant::GetLivesPerRound()
{
    uintptr_t address = GetVariantHook() + 654;
    return *reinterpret_cast<int8_t *>(address);
}

int8_t Variant::GetUseInfluencerSpawnPointSpawning()
{
    uintptr_t address = GetVariantHook() + 661;
    return *reinterpret_cast<int8_t *>(address);
}

bool Variant::GetUseCoopSpawning()
{
    uintptr_t address = GetVariantHook() + 662;
    return *reinterpret_cast<bool *>(address);
}

bool Variant::GetUseSwarmSpawning()
{
    uintptr_t address = GetVariantHook() + 663;
    return *reinterpret_cast<bool *>(address);
}

bool Variant::CheckIfExists(uintptr_t address, uint32_t value)
{
    char temp = 0;
    __int64 eval = 0;

    if (value > 0xD || (temp = value, eval = 1i64, ((unsigned __int16)(1 << temp) & address) == 0)) {
        eval = 0;
    }
    return eval != 0;
}

bool Variant::GetSpawnProtectionEnabled()
{
    uintptr_t address = GetVariantHook() + 652;
    return CheckIfExists(address, 10);
}

uint32_t Variant::GetSpawnProtectionDuration()
{
    double result = 0.0;
    uintptr_t address = GetVariantHook();
    if(!CheckIfExists(address + 652, 0xAu)) {
        return 0;
    }
    return *reinterpret_cast<uint32_t *>(address + 1288);
}

uint8_t Variant::GetRegulationRoundLimit()
{
    uintptr_t address = GetVariantHook() + 4288;
    return *reinterpret_cast<int8_t *>(address);
}

uint8_t Variant::GetRoundLimit()
{
    uintptr_t address = GetVariantHook() + 4248;
    int8_t temp_value = *reinterpret_cast<int8_t*>(address + 40);
    int8_t current_value = 0;

    if (temp_value > 0 && *reinterpret_cast<int32_t*>(address + 16) == 2) {
        ++temp_value;
    }

    if (temp_value >= 0) {
        current_value = temp_value;
    }

    if (current_value < 32) {
        return static_cast<uint8_t>(current_value);
    }
    return 32;
}

uint8_t Variant::GetRoundsTiedLimit()
{
    uintptr_t address = GetVariantHook() + 4261;
    return *reinterpret_cast<int8_t *>(address);
}

uint8_t Variant::GetEarlyVictoryRoundCount()
{
    uintptr_t address = GetVariantHook() + 4260;
    return *reinterpret_cast<int8_t *>(address);
}

bool Variant::IsEarlyRespawnEnabled()
{
    uintptr_t address = GetVariantHook() + 652;
    return CheckIfExists(address, 4);
}

uint8_t Variant::GetMaximumRespawnTime()
{
    uintptr_t address = GetVariantHook() + 657;
    return *reinterpret_cast<int8_t *>(address);
}

uint8_t Variant::GetMinimumRespawnTime()
{
    uintptr_t address = GetVariantHook() + 656;
    return *reinterpret_cast<int8_t *>(address);
}

uint8_t Variant::GetBetrayalPenaltyTime()
{
    uintptr_t address = GetVariantHook() + 659;
    return *reinterpret_cast<int8_t *>(address);
}

uint8_t Variant::GetSuicidePenaltyTime()
{
    uintptr_t address = GetVariantHook() + 658;
    return *reinterpret_cast<int8_t *>(address);
}

void Variant::HookVariant(uintptr_t ModuleBase)
{
    uintptr_t address = 0xB0F0D0;
    GetVariantH = hook_function<GetVariant>(ModuleBase, address, &GetVariantHook, &GetVariantA);
}
