# InfiniteExt
**InfiniteExt** is a customizable DLL Hook for Halo Infinite for interacting with the built-in HavokScript VM. This project is built on top of [Blamify's Gatekeeper](https://github.com/Blamify/Gatekeeper), with functionality updated for the latest build of Halo Infinite.

## Features
- [x] Hooking HavokScript
- [x] Hooks to Game Functions
- [x] Lua File Loading
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
InfiniteExt's command line is directly integrated into the built-in HavokScript VM of Halo Infinite. Here, you can run regular lua functions in addition to the custom C bindings which you can find a list for [here.](https://surasia.github.io/assets/env_alphabetical.json)


## Licenses
- [Minhook:](licenses/MinhookLicense.txt) The Minimalistic x86/x64 API Hooking Library for Windows.