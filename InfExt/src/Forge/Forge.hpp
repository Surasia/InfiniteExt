#ifndef FORGE_HPP
#define FORGE_HPP
#include <windows.h>

struct Forge {
public:
	/* Operators */
	Forge() = default;
	~Forge() = default;
	/* Public Functions */
	static void ToggleForgeHiddenCategories();
private:
	/* Public Variables */
	inline static bool isEnabled = false;
};

#endif
