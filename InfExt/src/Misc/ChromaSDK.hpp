#ifndef CHROMASDK_HPP
#define CHROMASDK_HPP
#include <cstdint>

struct ChromaSDK
{
public:
    /* Hook */
    static void HookChroma(uintptr_t ModuleBase);

private:
    /* Function Type Definitions */
    using NullChromaSDK = __int64(__fastcall *)(char *Format);
    static NullChromaSDK NullChromaSDKH;
    static NullChromaSDK NullChromaSDKA;

    /* Private Functions */
    static __int64 NullChromaSDKHook(char *Format);
};

#endif
