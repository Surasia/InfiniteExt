#include "ChromaSDK.hpp"
#include "../Memory.hpp"
#include <stdio.h>

/* Nulls out the print message for "ChromaSDK failed to load!" which can cause issues with stdin. */
int64_t ChromaSDK::NullChromaSDKHook(char *Format)
{
    return 0;
}

void ChromaSDK::HookChroma(uintptr_t ModuleBase)
{
    uintptr_t address = 0xD869C4;
    NullChromaSDKH = hook_function<NullChromaSDK>(ModuleBase, address, &NullChromaSDKHook, &NullChromaSDKA);
}