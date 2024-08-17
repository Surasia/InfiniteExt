#ifndef FORGE_HPP
#define FORGE_HPP
#include <windows.h>

struct Patches
{
public:
    /* Operators */
    Patches() = default;
    Patches(const Patches &) = default;
    Patches(Patches &&) = delete;
    Patches &operator=(const Patches &) = default;
    Patches &operator=(Patches &&) = delete;
    ~Patches() = default;
    /* Public Functions */
    static void ToggleForgeHiddenCategories();
    static void ToggleHUD();
    static void ToggleWatermark();
    static void ToggleKillVolumes();
};

#endif
