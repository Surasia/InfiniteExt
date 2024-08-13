#ifndef MEMORY_HPP
#define MEMORY_HPP
#include <windows.h>
#include <Minhook.h>

class Memory
{
public:
	/* Operators */
	Memory() = default;
	Memory(const Memory&) = default;
	Memory(Memory&&) = delete;
	Memory& operator=(const Memory&) = default;
	Memory& operator=(Memory&&) = delete;
	~Memory() = default;;
	/* Public Functions */
	static DWORD HookFunction(LPVOID pTarget, LPVOID pDetour, LPVOID pTrampoline);
	static DWORD OnAccessHookFunction(PVOID pTarget, LPVOID pDetour, LPVOID pTrampoline);
	static void WriteBytes(uintptr_t pAddress, BYTE* pBytes, UINT szSize);

private:
	/* Private Variables */
	static inline bool isMHInit = false;
	/* Private Functions */
	static UINT64 CheckCodeAccess(UINT64 startaddress);
};

template <typename T>
T hook_function(uintptr_t ModuleBase, uintptr_t offset, void* hook, T* original)
{
	T functionPointer = reinterpret_cast<T>(ModuleBase + offset);
	Memory::HookFunction(functionPointer, hook, original);
	return functionPointer;
}

#endif
