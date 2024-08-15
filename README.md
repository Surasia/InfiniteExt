# InfiniteExt
**InfiniteExt** is a customizable DLL Hook for Halo Infinite for interacting with the built-in HavokScript VM and tag system. This project is built on top of [Blamify's Gatekeeper](https://github.com/Blamify/Gatekeeper), with functionality updated for the latest build of Halo Infinite.

## Features/To-Do
- [x] Hooking HavokScript
- [x] Hooks to Game Functions
- [x] Lua File Loading
- [x] Tag Editing/Viewing
- [ ] Built-in Memory Editor
- [x] ImGui Integration
- [x] Forge Hidden Category Enabler
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
### Console
InfiniteExt's ImGui interface contains a command line that is directly integrated into the built-in HavokScript VM of Halo Infinite. Here, you can run regular lua functions in addition to the custom C bindings which you can find a list for [here.](https://surasia.github.io/assets/env_alphabetical.json)

### Debug Menu
The debug menu contains multiple toggles for:
- Enabling the Forge hidden category
- Enabling the debug watermark
- Disabling HUD
- Disabling kill volumes

### Tag Editor
InfiniteExt provides a tag window that allows you to load and view tags. Simply press the "Load Tags" button and the list will populate with tags sorted by their class. Currently, except for CMSW (CoatingSwatch) files, the list view only provides metadata for tags. For CMSW files however, you can click the "Edit Tag" button, which will open up a seperate window that will allow you to edit every property of the tag.

### Keybindings:
- Home: Reload Graphics Hook
- Insert: Show/Hide UI
- End: Hook/Unhook ImGui/DX12


## Licenses/Dependencies
- [Minhook:](licenses/MinhookLicense.txt) The Minimalistic x86/x64 API Hooking Library for Windows.
- [Dear Imgui:](licenses/ImGuiLicense.txt) Bloat-free Graphical User interface for C++ with minimal dependencies.
- [UniversalHookX (modified):](licenses/UniversalHookXLicense.txt): Universal graphical hook for Windows apps.
- [libinfinite (structs)](licenses/LibInfiniteLicense.txt): A library for working with Halo Infinites files.