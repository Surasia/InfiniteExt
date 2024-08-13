#ifndef HOOKS_HPP
#define HOOKS_HPP

#include <Windows.h>
#include <cstdio>
#include <mutex>
#include <thread>
#include <MinHook.h>

namespace Hooks {
	void Init();
	void Free();
	inline bool isShuttingDown;
}

#endif
