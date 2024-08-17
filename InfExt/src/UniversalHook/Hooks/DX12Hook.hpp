#ifndef HOOK_DIRECTX12_HPP
#define HOOK_DIRECTX12_HPP

#include <MinHook.h>
#include <Windows.h>
#include <d3d12.h>
#include <dxgi1_4.h>
#include <imgui_impl_dx12.h>
#include <imgui_impl_win32.h>

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")

namespace DX12
{
void Hook(HWND hwnd);
void Unhook();
} // namespace DX12

#endif
