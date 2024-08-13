#ifndef MENU_HPP
#define MENU_HPP

#include <Windows.h>
#include <string>
#include <imgui.h>
#include <imgui_impl_win32.h>

namespace Menu {
	void InitializeContext(HWND hwnd);
	void Render();

	inline bool shouldShowMenu = true;
}

#endif
