#ifndef MENU_HPP
#define MENU_HPP

#include <Windows.h>
#include <string>
#include <imgui.h>
#include <imgui_impl_win32.h>
#include <map>
#include "../../TagLoader/TagLoader.hpp"
#include "../../TagLoader/Types/Generated/Cmsw.hpp"

class Menu {
public:
    /* Public Functions */
    static void InitializeContext(HWND hwnd);
    static void Render();
    /* Public Variables */
    inline static bool shouldShowMenu = true;
};
#endif
