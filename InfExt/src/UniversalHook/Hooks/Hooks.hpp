#ifndef HOOKS_HPP
#define HOOKS_HPP

#include <MinHook.h>
#include <Windows.h>
#include <cstdio>
#include <mutex>
#include <thread>

namespace Hooks
{
void Init();
void Free();
inline bool isShuttingDown;
} // namespace Hooks

#endif
