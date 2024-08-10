#ifndef VARIANT_HPP
#define VARIANT_HPP
#include <cstdint>

struct Variant {
public:
    /* Hook */
    static void HookVariant(uintptr_t ModuleBase);
    static uintptr_t GetVariantHook();
    static const char *GetEngineName();
    static const char *GetVariantName();
    static bool GetTeamsEnabled();
    static bool GetTeamScoringEnabled();
    static bool GetRequisitionEnabled();
    static bool GetReqVehiclesEnabled();
    static bool GetReqConsumableWeaponsEnabled();
    static bool GetReqLoadoutWeaponsEnabled();
    static bool GetReqArmorModsEnabled();
    static bool GetActiveSpartanTrackingEnabled();
    static bool GetPassiveSpartanTrackingEnabled();
    static bool GetREQVehicleCapPerMapEnabled();
    static int8_t GetREQVehicleCapPerMap();
    static bool GetREQVehicleCapPerTeamEnabled();
    static int8_t GetREQVehicleCapPerTeam();
    static int8_t GetLivesPerRound();
    static int8_t GetUseInfluencerSpawnPointSpawning();
    static bool GetUseCoopSpawning();
    static bool GetUseSwarmSpawning();
    static bool GetSpawnProtectionEnabled();
    static uint32_t GetSpawnProtectionDuration();
    static uint8_t GetRegulationRoundLimit();
    static uint8_t GetRoundLimit();
    static uint8_t GetRoundsTiedLimit();
    static uint8_t GetEarlyVictoryRoundCount();
    static bool IsEarlyRespawnEnabled();
    static uint8_t GetMaximumRespawnTime();
    static uint8_t GetMinimumRespawnTime();
    static uint8_t GetBetrayalPenaltyTime();
    static uint8_t GetSuicidePenaltyTime();


private:
    /* Function Type Definitions */
    using GetVariant = uintptr_t(__fastcall *)();
    static GetVariant GetVariantH;
    static GetVariant GetVariantA;
    static bool CheckIfExists(uintptr_t address, uint32_t value);
};

#endif
