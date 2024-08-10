#include "ChromaSDK.hpp"
#include "../Memory.hpp"

/* Declare private variables. */
ChromaSDK::NullChromaSDK ChromaSDK::NullChromaSDKH = nullptr;
ChromaSDK::NullChromaSDK ChromaSDK::NullChromaSDKA = nullptr;

/* Nulls out the print message for "ChromaSDK failed to load!" which can cause issues with stdin. */
__int64 ChromaSDK::NullChromaSDKHook(char *Format)
{
    return 0;
}

void ChromaSDK::HookChroma(uintptr_t ModuleBase)
{
    uintptr_t address = 0x8CF168;
    NullChromaSDKH = hook_function<NullChromaSDK>(ModuleBase, address, &NullChromaSDKHook, &NullChromaSDKA);
}
