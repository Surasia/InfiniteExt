#include "Hooks.hpp"
#include "../menu/menu.hpp"
#include "../utils/utils.hpp"
#include "DX12Hook.hpp"

static HWND g_hWindow = NULL;
static std::mutex g_mReinitHooksGuard;

static DWORD WINAPI ReinitializeGraphicalHooks(LPVOID lpParam)
{
    std::lock_guard<std::mutex> guard{g_mReinitHooksGuard};

    HWND hNewWindow = Utils::GetProcessWindow();
    while (hNewWindow == reinterpret_cast<HWND>(lpParam))
    {
        hNewWindow = Utils::GetProcessWindow();
    }

    Hooks::isShuttingDown = true;

    Hooks::Free();
    Hooks::Init();

    Hooks::isShuttingDown = false;
    Menu::shouldShowMenu = true;

    return 0;
}

static WNDPROC oWndProc;
static LRESULT WINAPI WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (uMsg == WM_KEYDOWN)
    {
        if (wParam == VK_INSERT)
        {
            Menu::shouldShowMenu = !Menu::shouldShowMenu;
            return 0;
        }
        else if (wParam == VK_HOME)
        {
            HANDLE hHandle = CreateThread(NULL, 0, ReinitializeGraphicalHooks, NULL, 0, NULL);
            if (hHandle != NULL)
                CloseHandle(hHandle);
            return 0;
        }
        else if (wParam == VK_END)
        {
            Hooks::isShuttingDown = true;
            Utils::UnloadDLL();
            return 0;
        }
    }
    else if (uMsg == WM_DESTROY)
    {
        HANDLE hHandle = CreateThread(NULL, 0, ReinitializeGraphicalHooks, hWnd, 0, NULL);
        if (hHandle != NULL)
            CloseHandle(hHandle);
    }

    LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
    if (Menu::shouldShowMenu)
    {
        ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
    }

    return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

namespace Hooks
{
void Init()
{
    g_hWindow = Utils::GetProcessWindow();
    DX12::Hook(g_hWindow);
    oWndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(g_hWindow, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WndProc)));
}

void Free()
{
    if (oWndProc)
    {
        SetWindowLongPtr(g_hWindow, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(oWndProc));
    }

    MH_DisableHook(MH_ALL_HOOKS);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    DX12::Unhook();
}
} // namespace Hooks
