#ifndef CHROMASDK_HPP
#define CHROMASDK_HPP
#include <cstdint>

struct ChromaSDK
{
public:
    /* Operators */
    ChromaSDK() = default;
    ChromaSDK(const ChromaSDK &) = default;
    ChromaSDK(ChromaSDK &&) = delete;
    ChromaSDK &operator=(const ChromaSDK &) = default;
    ChromaSDK &operator=(ChromaSDK &&) = delete;
    ~ChromaSDK() = default;
    /* Hook */
    static void HookChroma(uintptr_t ModuleBase);

private:
    /* Function Type Definitions */
    using NullChromaSDK = int64_t(__fastcall *)(char *Format);
    static inline NullChromaSDK NullChromaSDKH = nullptr;
    static inline NullChromaSDK NullChromaSDKA = nullptr;

    /* Private Functions */
    static int64_t NullChromaSDKHook(char *Format);
};

#endif
