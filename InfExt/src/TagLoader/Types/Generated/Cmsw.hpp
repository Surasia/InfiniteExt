#ifndef CMSW_HPP
#define CMSW_HPP

#pragma pack(push,1)
#include "../infiniteStructs.hpp"
#include <stdint.h>

struct cmsw {
    struct AnyTag {
        uint64_t vtable_space;
        struct internal_struct {
            uint32_t global_tag_ID;
            uint32_t local_tag_handle;
        };
        struct internal_struct internal_struct_ent;
    };
    struct AnyTag AnyTag_ent;
    struct tagReference Parent;
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
