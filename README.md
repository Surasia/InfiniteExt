# InfiniteExt
**InfiniteExt** is a customizable DLL Hook for Halo Infinite featuring a **Lua API** for interacting with game objects and functions. This project is built on top of [Blamify's Gatekeeper](https://github.com/Blamify/Gatekeeper), with functionality updated for the latest build of Halo Infinite.

## Features
- [x] Built-in Lua VM
- [x] Hooks to Game Functions
- [ ] Tag Viewing
- [ ] Built-in Memory Editor
- [ ] ImGui Integration
- [ ] Game Engine Hooks

> [!TIP]
> PRs and Feature requests are appreciated!


## Installation
InfiniteExt requires Easy Anti Cheat to be disabled, which can be achieved by moving the `/game` folder into the main installation directory.
- Steam: `{path to SteamLibrary}/steamapps/common/Halo Infinite/game` -> `{path to SteamLibrary}/steamapps/common/Halo Infinite`
- Microsoft Store: `{path to XboxGames}/Halo Infinite/Content/game` -> `{path to XboxGames}/Halo Infinite/Content/`

For hooking InfiniteExt to Halo Infinite, the USER32 DLL has to be replaced with InfiniteExt. In a Hex editor of your choice, open the `HaloInfinite.exe` executable, search for `USER32.DLL` and replace with `InfExt.DLL`.

> [!IMPORTANT]
> Replace the User32 DLL inside the main HaloInfinite.exe, the one you copied from /game. This file should be around 80-90MBs depending on version.

## Building
This project can be built using Visual Studio 2022 (vc143) with `vcpkg` installed. To install `vcpkg`, follow [these instructions.](https://learn.microsoft.com/en-us/vcpkg/get_started/get-started-msbuild). Previous versions of Visual Studio haven not been tested.

> [!NOTE]
> The current project is not cross-platform compatible due to a multitude of Microsoft-specific extensions of C++ being used. Usage on Linux using Wine has not been tested.

## Usage
InfiniteExt implements a simple command-line with a Lua 5.4 VM interpreter, powered by [Sol2](https://github.com/ThePhD/sol2/). The `base, os, io, string` modules are loaded by default, and can be used to perform generic lua functionality. Alongside the base functionality, Lua hooks to C++ functions are also used:

- "Variant_GetVariantHook
- "Variant_GetEngineName
- "Variant_GetVariantName
- "Variant_GetTeamsEnabled
- "Variant_GetTeamScoringEnabled
- "Variant_GetRequisitionEnabled
- "Variant_GetReqVehiclesEnabled
- "Variant_GetReqConsumableWeaponsEnabled
- "Variant_GetReqLoadoutWeaponsEnabled
- "Variant_GetReqArmorModsEnabled
- "Variant_GetActiveSpartanTrackingEnabled
- "Variant_GetPassiveSpartanTrackingEnabled
- "Variant_GetREQVehicleCapPerMapEnabled
- "Variant_GetREQVehicleCapPerMap
- "Variant_GetREQVehicleCapPerTeamEnabled
- "Variant_GetREQVehicleCapPerTeam
- "Variant_GetLivesPerRound"
- "Variant_GetUseInfluencerSpawnPointSpawning
- "Variant_GetUseCoopSpawning
- "Variant_GetUseSwarmSpawning
- "Variant_GetSpawnProtectionEnabled
- "Variant_GetSpawnProtectionDuration
- "Variant_GetRegulationRoundLimit
- "Variant_GetRoundLimit
- "Variant_GetRoundsTiedLimit
- "Variant_GetEarlyVictoryRoundCount
- "Variant_IsEarlyRespawnEnabled
- "Variant_GetMaximumRespawnTime
- "Variant_GetMinimumRespawnTime
- "Variant_GetBetrayalPenaltyTime
- "Variant_GetSuicidePenaltyTime

As the project matures, these functions will include their own documentation and more will be added.


## Licenses
- [Minhook:]("licenses/MinhookLicense.txt") The Minimalistic x86/x64 API Hooking Library for Windows.
- [Sol2:]("licenses/Sol2License.txt") Lua API wrapper with advanced features and top notch performance.
- [Lua:]("licenses/LuaLicense.txt") Lua is a powerful, efficient, lightweight, embeddable scripting language. It supports procedural programming, object-oriented programming, functional programming, data-driven programming, and data description. 