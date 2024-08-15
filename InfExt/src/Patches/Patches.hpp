#ifndef FORGE_HPP
#define FORGE_HPP
#include <windows.h>

struct Patches {
public:
	/* Operators */
	Patches() = default;
	~Patches() = default;
	/* Public Functions */
	static void ToggleForgeHiddenCategories();
	static void ToggleHUD();
	static void ToggleWatermark();
	static void ToggleKillVolumes();
};

#endif
