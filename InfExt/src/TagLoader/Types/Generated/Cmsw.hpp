#ifndef CMSW_HPP
#define CMSW_HPP

#pragma pack(push, 1)
#include "../infiniteStructs.hpp"
#include <cstdint>

struct CoatingSwatchPODTag
{
    struct AnyTag
    {
        uint64_t vtableSpace;
        struct internalStruct
        {
            uint32_t globalTagID;
            uint32_t localTagHandle;
        };
        struct internalStruct internalStructEnt;
    };
    struct AnyTag anyTagEnt;
    struct tagReference parent;
    struct vector2D colorAndRoughnessTextureTransform;
    struct vector2D normalTextureTransform;
    struct tagReference colorGradientMap;
    realRGBColor gradientTopColor;
    realRGBColor gradientMidColor;
    realRGBColor gradientBottomColor;
    float roughnessWhite;
    float roughnessBlack;
    struct tagReference normalDetailMap;
    float metallic;
    float ior;
    float albedoTintSpec;
    realRGBColor scratchColor;
    float scratchBrightness;
    float scratchRoughness;
    float scratchMetallic;
    float scratchIOR;
    float scratchAlbedoTintSpec;
    float sssIntensity;
    float emissiveIntensity;
    float emissiveAmount;
};

#pragma pack(pop)
#endif
