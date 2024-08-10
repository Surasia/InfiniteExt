#include "LuaHook.hpp"
#include "../Variant/Variant.hpp"


sol::state LuaVM::lua;

void LuaVM::HookVariantFunctions()
{
    lua["Variant_GetVariantHook"] = &Variant::GetVariantHook;
    lua["Variant_GetEngineName"] = &Variant::GetEngineName;
    lua["Variant_GetVariantName"] = &Variant::GetVariantName;
    lua["Variant_GetTeamsEnabled"] = &Variant::GetTeamsEnabled;
    lua["Variant_GetTeamScoringEnabled"] = &Variant::GetTeamScoringEnabled;
    lua["Variant_GetRequisitionEnabled"] = &Variant::GetRequisitionEnabled;
    lua["Variant_GetReqVehiclesEnabled"] = &Variant::GetReqVehiclesEnabled;
    lua["Variant_GetReqConsumableWeaponsEnabled"] = &Variant::GetReqConsumableWeaponsEnabled;
    lua["Variant_GetReqLoadoutWeaponsEnabled"] = &Variant::GetReqLoadoutWeaponsEnabled;
    lua["Variant_GetReqArmorModsEnabled"] = &Variant::GetReqArmorModsEnabled;
    lua["Variant_GetActiveSpartanTrackingEnabled"] = &Variant::GetActiveSpartanTrackingEnabled;
    lua["Variant_GetPassiveSpartanTrackingEnabled"] = &Variant::GetPassiveSpartanTrackingEnabled;
    lua["Variant_GetREQVehicleCapPerMapEnabled"] = &Variant::GetREQVehicleCapPerMapEnabled;
    lua["Variant_GetREQVehicleCapPerMap"] = &Variant::GetREQVehicleCapPerMap;
    lua["Variant_GetREQVehicleCapPerTeamEnabled"] = &Variant::GetREQVehicleCapPerTeamEnabled;
    lua["Variant_GetREQVehicleCapPerTeam"] = &Variant::GetREQVehicleCapPerTeam;
    lua["Variant_GetLivesPerRound"] = &Variant::GetLivesPerRound;
    lua["Variant_GetUseInfluencerSpawnPointSpawning"] = &Variant::GetUseInfluencerSpawnPointSpawning;
    lua["Variant_GetUseCoopSpawning"] = &Variant::GetUseCoopSpawning;
    lua["Variant_GetUseSwarmSpawning"] = &Variant::GetUseSwarmSpawning;
    lua["Variant_GetSpawnProtectionEnabled"] = &Variant::GetSpawnProtectionEnabled;
    lua["Variant_GetSpawnProtectionDuration"] = &Variant::GetSpawnProtectionDuration;
    lua["Variant_GetRegulationRoundLimit"] = &Variant::GetRegulationRoundLimit;
    lua["Variant_GetRoundLimit"] = &Variant::GetRoundLimit;
    lua["Variant_GetRoundsTiedLimit"] = &Variant::GetRoundsTiedLimit;
    lua["Variant_GetEarlyVictoryRoundCount"] = &Variant::GetEarlyVictoryRoundCount;
    lua["Variant_IsEarlyRespawnEnabled"] = &Variant::IsEarlyRespawnEnabled;
    lua["Variant_GetMaximumRespawnTime"] = &Variant::GetMaximumRespawnTime;
    lua["Variant_GetMinimumRespawnTime"] = &Variant::GetMinimumRespawnTime;
    lua["Variant_GetBetrayalPenaltyTime"] = &Variant::GetBetrayalPenaltyTime;
    lua["Variant_GetSuicidePenaltyTime"] = &Variant::GetSuicidePenaltyTime;
}


void LuaVM::InitializeLua()
{
    lua.open_libraries(sol::lib::base, sol::lib::os, sol::lib::io, sol::lib::string);
    lua["exit"] = [](int code) {
        std::cout << "Exiting with code: " << code << std::endl;
        std::exit(code);
    };
}

void LuaVM::CleanLua()
{
    lua.collect_garbage();
}

void LuaVM::ProcessCommand()
{
    std::string command = "";

    std::cout << "> ";
    std::getline(std::cin, command);
    sol::protected_function_result result = lua.script(command, [](lua_State *, sol::protected_function_result pfr) { return pfr; });

    if (result.valid()) {
        sol::optional<std::string> output = result;
        if (output) {
            std::cout << std::format("{} \n", *output);
        } else {
            std::cout << "\n";
        }
    } else {
        sol::error err = result;
        std::cout << err.what() << std::endl;
    }
}
