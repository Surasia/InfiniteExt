#ifndef INFINITESTRUCT_HPP
#define INFINITESTRUCT_HPP


/* File From libinfinite by Coarforge */
/* Source: https://github.com/Z-15/Halo-Infinite-Tag-Editor/blob/master/Halo-Infinite-Tag-Editor/InfiniteModuleEditor/Slipspace/Tag.cs */

#include <array>
#include <cstdint>
#pragma pack(push, 1)

using stringId = uint32_t;
using tagblock = struct tagblock;

template <typename t>
struct tagBlock
{
    void *Elements;
    t *block; // CAUTION: this value gets overwritten by the loader to point to the struct holding the data of this block
    uint32_t count;
};

/*
_42
- to assign the data, just use the next entry in the data table (iterating over all that are used)
- looks like they are in region 1 as well, or at least they can be
*/
struct dataReference
{
    void *data;
    uint64_t TypeInfo;
    uint32_t unknown;
    uint32_t size;
};

/* _41 */
struct tagReference
{
    void *TypeInfo; // CAUTION: the loader puts the pointer to the root struct of the referenced tag here
    uint32_t globalId;
    uint64_t assetId;
    union
    {
        uint32_t tagClass;
        std::array<char, 4> tagClassString;
    };
    uint32_t localHandle;
};

/*
_43
- these don't get loaded by default
*/
template <typename t>
struct externalResource
{
    t *block;
    /*
    * Points to the struct that holds more info about the resource
    * The actual resource data has to be requested from the moduleItem(s) for it
    */
    uint32_t Handle; // Index of the CTE (it's not really needed once the tag has been loaded, no there's no point in keeping a pointer to it here
    // when ther isn't really enough space without overwriting unknown, which could turn out to be important)
    uint32_t unknown;
};

/* _10 */
struct shortPoint2D
{
    uint16_t x;
    uint16_t y;
};

/* _12 */
using rgbColor = struct rgbColor
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a; // unused
};
using argbColor = rgbColor;

/* _16 */
struct point2D
{
    float x;
    float y;
};

/* _18 */
struct vector2D
{
    float x;
    float y;
};

/* _17 */
struct point3D
{
    float x;
    float y;
    float z;
};

/* _19 */
struct vector3D
{
    float x;
    float y;
    float z;
};

/* _20 */
using realARGBColor = struct realARGBColor
{
    float a;
    float r;
    float g;
    float b;
};

/* _1F */
using realRGBColor = struct realRGBColor
{
    float r;
    float g;
    float b;
};

/* _1A */
using realQuaternion = struct realQuaternion
{
    float x;
    float y;
    float z;
    float w;
};

/* _1B */
using realEulerAngles2D = struct realEulerAngle2D
{
    float x;
    float y;
};

/* _1C */
using realEulerAngle3D = struct realEulerAngle3D
{
    float x;
    float y;
    float z;
};

/* _1D */
using realPlane2D = struct realPlane2D
{
    float x;
    float y;
    float d;
};

/* _1E */
using realPlane3D = struct realPlane3D
{
    float x;
    float y;
    float z;
    float d;
};

/* _23 */
using shortBounds = struct shortBounds
{
    uint16_t min;
    uint16_t max;
};

/* _25 */
using realBounds = struct realBounds
{
    float min;
    float max;
};

/* _26 */
using realFractionBounds = struct realBounds;

/* _8 */
using angle = float;

/* _2E */
using shortBlockIndex = uint16_t;

/* _2F */
using customShortBlockIndex = uint16_t;

/* _30 */
using longBlockIndex = uint32_t;

#pragma pack(pop)

#endif
